#!/bin/sh

CUT=/usr/bin/cut
DIFF=/usr/bin/diff
ECHO=/bin/echo
FIND=/usr/bin/find

challenges=$(${FIND} . -name 'challenge-*' -type f -executable)
for c in ${challenges}; do
    id=$(${ECHO} ${c} | ${CUT} -d '-' -f 2)
    inputs=$(${FIND} input/ -name "${id}*")
    for input in ${inputs}; do
        output_file=$(${ECHO} ${input} | ${CUT} -d '/' -f 2)
        if [ -e "output/${output_file}" ]; then
            ${c} ${input} | ${DIFF} -q "output/${output_file}" - >/dev/null
            if [ $? -ne 0 ]; then
                ${ECHO} "${input} failed" >&2
            fi
        else
            ${ECHO} "${output_file} does not exist" >&2
        fi
    done
done
