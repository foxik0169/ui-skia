import os
import sys

def do_iterate(path):
	abpath = os.path.abspath(path)
	
	for dirp, dirn, filenames in os.walk(abpath):
		for filename in filenames:
			# print line
			print('target_link_libraries(UI ${PROJECT_SOURCE_DIR}/' + os.path.relpath(os.path.join(dirp, filename), ".").replace("\\", "/") + ")")
	pass


if __name__ == '__main__':
	
	print ("Get libraries v0.1")
	
	if len(sys.argv) < 2:
		print('# USAGE: get_libraries [path]\n  Returns cmake standardized "target_link_libraries" filenames.')
	else:
		do_iterate(sys.argv[1])
		pass
	
	pass