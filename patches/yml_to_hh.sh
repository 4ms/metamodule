#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 path/to/patchfile.yml"
  exit 1
fi

# Input file
file="$1"

# Check if file exists and is a .yml file
if [[ ! -f "$file" || "${file##*.}" != "yml" ]]; then
  echo "Error: File does not exist or is not a .yml file."
  exit 1
fi

# Extract base directory and name
dir=$(dirname "$file")
base=$(basename "$file" .yml)
new_file="$dir/$base.hh"
patchname="patch_"$base
sanitized_patchname=$(echo "$patchname" | tr ' ' '_')

header="// Automatically generated, do not edit
static const char $sanitized_patchname[] =
	R\"("

footer=")\";
"

# Write header, original content, and footer into the temp file
{
  echo "$header"
  cat "$file"
  echo "$footer"
} > "$new_file"


echo "Processed: $file -> $new_file"

