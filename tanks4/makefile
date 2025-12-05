patch: tanks_final.cpython-310.pyc.linux 
patch: tanks_final.cpython-313.pyc.linux
patch: tanks_final.cpython-314.pyc.linux
patch: tank_launcher_linux.py

tank_launcher_linux.py: tank_launcher.py
	sed "s/\.pyc/\.pyc\.linux/g" < $< > $@

tanks_final.cpython-3%.pyc.linux: tanks_final.cpython-3%.pyc.delta
	rdiff patch tanks_final.cpython-3$*.pyc $< $@

.PHONY: clean
clean:
	-rm tanks_final.cpython-310.pyc.linux
	-rm tanks_final.cpython-313.pyc.linux
	-rm tanks_final.cpython-314.pyc.linux
	-rm tank_launcher_linux.py

run: patch
	python tank_launcher_linux.py

# this is for me!
tanks4-patcher.zip: *.delta makefile tanks4-patcher-README.md tanks4-patcher-LICENSE.txt
	7z a $@ $^
