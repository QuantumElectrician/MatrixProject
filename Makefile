all:
	gcc main.cpp Definition.hpp Definition.cpp -fopenmp
analyse:
	xcodebuild | xcpretty -r json-compilation-database
	pvs-studio-analyzer analyze -f build/reports/compilation_db.json
	plog-converter -a GA:1,2 -t tasklist -o ./Report.tasks PVS-Studio.log	
