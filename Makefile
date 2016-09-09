all:
	g++ csv_parser.cpp `root-config --glibs --cflags` -o csv_parser
