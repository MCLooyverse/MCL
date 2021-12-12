#!/bin/sh

# Clear old masters
rm *.h


# Go through the cpp* dirs in reverse order
for dir in $(echo cpp* | sed "s/ /\n/g" | sort -r); do
	for header in $dir/*.h; do
		name=${header#$dir/}
		ver=$(cat $dir/__cplusplus)

		ifkind="#if"
		if [ -f $name ]; then
			ifkind="#elif"
		fi

		printf "%s __cplusplus >= %s\n\t#include \"%s\"\n" \
			$ifkind $ver $header >> $name
	done
done

# Including a header in an unsupported std should cause an error
for header in *.h; do
	echo -e "#else\n\t#error \"\\\"mcl/${header}\\\" does not support this std version\"\n#endif\n" >> $header
done
