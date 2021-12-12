all:
	make headers utils readme

README.pdf: README.md
	pandoc README.md -o README.pdf

headers:
	/bin/sh makeMasters.sh

utils:
	for u in utils/*; do make -C u; done

README:
	make README.pdf
readme:
	make README.pdf

clean:
	rm README.pdf
