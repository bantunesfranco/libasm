#!/bin/bash

flags="-Wall -Wextra -Werror -fno-pie -no-pie"
includes="-I tests/ft_asm.h"

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
		filename="${filename#tests/ft_}"

		# Compile the C++ file with libasm.a
		c++ $flags "$file" $includes -L. -lasm -o "$filename"

		# Run the compiled file
		./"$filename" 2>> "$output"

		# Check return value
		if [[ $? -ne 0 ]]; then
			error=1
		fi

		# Remove the compiled file
		rm "$filename"
	fi
done

exit $error