#!/bin/bash

flags="-Wall -Wextra -Werror -fno-pie -no-pie -g -fsanitize=address"
includes="-I tests"

output="results.txt"
libasm="libasm.a"
error=0

if [[ ! -f "$libasm" ]]; then
	echo "libasm.a not found"
	exit 1
fi

# Creates the output file
if [[ -f "$output" ]]; then
	rm "$output"
fi
touch "$output"

# Compile each C++ file with libasm.a
for file in tests/*.cpp; do
	if [[ -f "$file" ]]; then
		# Extract the filename without extension and prefix
		filename="${file%.*}"
		filename="${filename#tests/}"

		# Compile the C++ file with libasm.a
		c++ $flags "$file" $includes -L. -lasm -o "$filename"

		# Run the compiled file
		echo "------- $filename -------" >> "$output"
		./"$filename" 2>> "$output"
		echo "" >> "$output"

		# Check return value
		if [[ $? -ne 0 ]]; then
			error=1
		fi

		# Remove the compiled file
		# rm "$filename"
	fi
done

echo ""
result=`cat $output | grep "memory leaks"`

if [[ -z "$result" ]]; then
	echo -e "\033[1;32mNo memory leaks\033[0m"
else
	echo -e "\033[1;31mMemory leaks found\033[0m"
	error=1
fi

if [[ $error -eq 1 ]]; then
	echo "See $output for more details"
fi

exit $error