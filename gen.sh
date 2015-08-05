#!/usr/bin/env bash

cd `dirname $0`

rejected=''
forced=''
project=''
used=''
external=''
tmp_includes=''
includes=''
> /tmp/__codeGen_functionsPrototypes
> /tmp/__codeGen_functionsResolution

for arg in $@; do
    if [ "$arg" == '--list' ] || [ "$arg" == '-l' ]; then
	cat <<EOF
Available projects :
`ls -1 --color=never projects | cat -n`
EOF
	exit 0
    elif [ "${arg:0:5}" == '--no-' ]; then
	rejected+=" ${arg:5}"
    elif [ "${arg:0:8}" == '--force-' ]; then
	forced+=" ${arg:8}"
    else
	project=`basename -- $arg`
    fi
done

[ -z "$project" ] && echo "Usage $0 [-l|--list] [--no-flag]... [--force-flag]... project_name" >&2 && exit 1

[ -d projects/$project ] || {
    cat <<EOF
Project $project does not exist.

Available projects :
`ls -1 --color=never projects | cat -n`
EOF
    exit 1
}

echo "Generating project $project..."

get_function_list_from_file() {
    functionList=$(grep -n '/\*.*function.*\*/' $1)
    for f in $forced; do
	newFunctionList=$(grep " $f " <<< "$functionList")
	if [ "$newFunctionList" == '' ]; then
	    echo -e "\033[31m\`$f\` flag not found in \"$1\". Flag \`--force-$f\` will be ignored\033[0m" >&2
	else
	    functionList="$newFunctionList"
	fi
    done

    for r in $rejected; do
	newFunctionList=$(grep -v " $r " <<< "$functionList")
	if [ "$newFunctionList" == '' ]; then
	    echo -e "\033[33mYou have suppressed too many flags for file \"$1\". Flag \`--no-$r\` will be ignored\033[0m" >&2
	else
	    functionList="$newFunctionList"
	fi
    done
    echo "$functionList"
}

get_function_name_from_prototype() {
    cut -d '(' -f1 <<< "$1" | tr -s '	' ' '  | cut -d ' ' -f2
}

get_function_includes_from_prototype() {
    grep -q '/\*.*\*/$' <<< "$1" && {
	tmp_includes+=" $(cut -d '/' -f2 <<< "$1" | cut -d '*' -f2)"
	includes+=" $(cut -d '/' -f2 <<< "$1" | cut -d '*' -f2)"
    }
}

display_prototype() {
    grep -q '/\*.*\*/$' <<< "$1" && cut -d '/' -f1 <<< "$1" || echo "$1"
}

get_function_from_file() {
    functionList=$(get_function_list_from_file $1)
    rand=$((RANDOM % $(wc -l <<< "$functionList") + 1))
    functionStartLine=$(head -n $rand <<< "$functionList" | tail -n 1 | cut -d ':' -f1)
    endOfFileLen=$(($(wc -l $1 | cut -d ' ' -f1) - $functionStartLine))
    nextFunctionStartLine=$(tail -n $endOfFileLen $1 | grep -n '/\*.*function.*\*/' | head -n 1 | cut -d ':' -f1)
    functionPrototype=$(tail -n $endOfFileLen $1 | head -n 1)
    display_prototype "$functionPrototype"
    display_prototype "$functionPrototype" >> /tmp/__codeGen_functionsPrototypes
    if [ -z "$nextFunctionStartLine" ]; then
	tail -n $(($endOfFileLen - 1)) $1
    else
	functionLen=$(($nextFunctionStartLine - 3))
	tail -n $(($endOfFileLen - 1)) $1 | head -n $functionLen
    fi
    get_function_includes_from_prototype "$functionPrototype";
    grep -q '^.*);.*$' <<< "$functionPrototype" && {
	external+=" $(get_function_name_from_prototype "$functionPrototype")"
    }
    echo $(basename $1 | cut -d '.' -f1) $(get_function_name_from_prototype "$functionPrototype") >> /tmp/__codeGen_functionsResolution
    used+="$(head -n $rand <<< "$functionList" | tail -n 1 | cut -d ':' -f2 | cut -d '*' -f2)"
}

get_function_code() {
    if [ -f projects/$project/sources/$1.c ]; then
	get_function_from_file projects/$project/sources/$1.c
    elif [ -f sources/$1.c ]; then
	get_function_from_file sources/$1.c
    else
	echo "Unable to resolve symbol \`$1\` wanted in \"$(readlink -f $2)\"" >&2
	exit 1
    fi
}

display_used_flags() {
    > /tmp/__codeGen_usedFlags
    for flag in $used; do
	echo "$flag" >> /tmp/__codeGen_usedFlags
    done
    echo -en "Used flags in this project:\033[33m"
    for flag in $(grep -v 'function' /tmp/__codeGen_usedFlags | sort -u); do
	echo -n " $flag"
    done
    echo -e "\033[0m"
    rm -f /tmp/__codeGen_usedFlags 2>&-
}

display_external_functions() {
    > /tmp/__codeGen_externalFunctions
    for f in $external; do
	echo "$f" >> /tmp/__codeGen_externalFunctions
    done
    echo -en "External (libc) functions used in this project:\033[33m"
    for f in $(sort -u /tmp/__codeGen_externalFunctions); do
	echo -n " $f"
    done
    echo -e "\033[0m"
    rm -f /tmp/__codeGen_externalFunctions 2>&-
}

display_used_includes() {
    > /tmp/__codeGen_includesUsed
    for include in $includes; do
	echo "$include" >> /tmp/__codeGen_includesUsed
    done
    echo -en "Header file used in this project:\033[33m"
    for include in $(sort -u /tmp/__codeGen_includesUsed); do
	echo -n " $include"
    done
    echo -e "\033[0m"
    rm -f /tmp/__codeGen_includesUsed 2>&-

}

mkdir -p target/$project || exit 1

add_tmp_include() {
    > /tmp/__codeGen_tmpInclude
    for include in $tmp_includes; do
	echo "$include" >> /tmp/__codeGen_tmpInclude
    done
    for include in $(sort -u /tmp/__codeGen_tmpInclude); do
	echo "#include <$include>"
    done
    echo "#include \"$project.h\""
    rm -f /tmp/__codeGen_tmpInclude 2>&-
}

create_project_header() {
    echo '#pragma once' > target/$project/$project.h
    echo >> target/$project/$project.h
    oldIFS=$IFS
    IFS='
'
    [ -f projects/$project/files/$project.h ] && cat projects/$project/files/$project.h >> target/$project/$project.h
    for f in $(cat /tmp/__codeGen_functionsPrototypes); do
	echo -n $f >> target/$project/$project.h
	grep -q ';$' <<< "$f" || echo -n ';' >> target/$project/$project.h
	echo >> target/$project/$project.h
    done
    IFS=$oldIFS;
}

load_plugins() {
    oldIFS=$IFS
    IFS='
'
    if [ -f projects/$project/PLUGINS ]; then
	echo "Loading plugins"
	for line in `cat projects/$project/PLUGINS`; do
	    name=$(cut -d' ' -f1 <<< "$line")
	    repo=$(cut -d' ' -f2 <<< "$line")
	    mkdir -p plugins || exit 1
	    [ -d "plugins/$name" ] && {
		pushd plugins/$name && git pull
		popd
	    } || {
		mkdir plugins/$name && pushd plugins/$name && git clone $repo .
		popd
	    }
	done
    fi
    IFS=$oldIFS
}

load_plugins

for file in `ls -1 projects/$project/files`; do
    > target/$project/$file
    tmp_includes=''
    oldIFS=$IFS
    IFS='
'
    for line in `cat projects/$project/files/$file`; do
	# if $(grep -q '^__codeGen_plugin_.*__.*$' <<< "$line"); then
	#     IFS=$oldIFS;
	#     get_function_code $line projects/$project/files/$file >> target/$project/$file
	# el
	if $(grep -q '^__codeGen__.*$' <<< "$line"); then
	    IFS=$oldIFS;
	    get_function_code $line projects/$project/files/$file >> target/$project/$file
	else
	    echo $line >> target/$project/$file
	fi
	IFS='
'
    done
    IFS=$oldIFS
    add_tmp_include > /tmp/__codeGen_sortedInclude
    cat target/$project/$file >> /tmp/__codeGen_sortedInclude
    mv /tmp/__codeGen_sortedInclude target/$project/$file
done

for file in `ls -1 target/$project`; do
    oldIFS=$IFS
    IFS='
'
    for func in `cat /tmp/__codeGen_functionsResolution`; do
	codeGen=$(cut -d ' ' -f1 <<< "$func")
	replace=$(cut -d ' ' -f2 <<< "$func")
	sed "s/$codeGen/$replace/" target/$project/$file > /tmp/__codeGen_tmpSedFile
	mv /tmp/__codeGen_tmpSedFile target/$project/$file
    done
    IFS=$oldIFS
done


create_project_header

display_used_flags
display_external_functions
display_used_includes
cat <<EOF
Generated project is in target/$project.
Don't forget to test it !
EOF

rm -f /tmp/__codeGen_functionsResolution /tmp/__codeGen_functionsPrototypes 2>&-

exit 0
