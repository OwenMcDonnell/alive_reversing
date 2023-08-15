# Find all .cpp files in the current directory and subdirectories
find . -type f -name "*.cpp" | while read file; do
  # Use sed to replace the pattern case ReliveTypes::e*: with case ReliveTypes::e*.Value():
  # The -i option means to edit the file in place
  # The -E option means to use extended regular expressions
  # The -e option means to execute the following expression
  # The s command means to substitute the matched pattern with the replacement
  # The /g flag means to replace all occurrences in the line
  # The /I flag means to ignore case
  # The pattern is case ReliveTypes:: followed by any number of characters (*) followed by a colon (:)
  # The replacement is the same as the pattern, but with .Value() added before the colon
  # The parentheses () and backslash \1 are used to capture and reference the matched pattern
  sed -i -E -e 's/(case ReliveTypes::.*):/\1.Value():/gI' "$file"
done