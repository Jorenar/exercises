#!/usr/bin/env sh

read letter

if [ "$(echo $letter | cut -c2)" = "=" ]; then
    letter="$(echo $letter | cut -c1)"
    flag=1
else
    letter="$(echo $letter | awk '{print tolower($0)}')"
fi

while IFS= read -r line; do
    if [ -n "$line" ]; then
        [ -z "$flag" ] && line="$(echo $line | awk '{print tolower($0)}')"
        echo "$line" | awk -F"$letter" '{print NF-1}'
    else
        echo "0"
    fi
done

# This should work, but NO, because BaCa
#
# #!/usr/bin/env sh
#
# read letter
#
# [ "$(echo $letter | cut -c2)" = "=" ] && letter="$(echo $letter | cut -c1)" || flag="-i"
#
# while IFS= read -r line; do
#     echo "$line" | egrep -o $flag "$letter" | wc -l
# done
