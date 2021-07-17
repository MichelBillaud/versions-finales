#
# Makefile pour compilation/execution de projets Java
# + tests unitaires
#

project_name = demo-1.0

main_class = appli.Prog

test_classes = $(shell \
	find test \( -name "*Test.java" -o -name "Test*.java" \)  | \
	sed -e "s,test/,," -e "s/.java$$//" -e "s,/,.,g" )


SOURCES = $$(find src  -name "*.java")
TESTS =   $$(find test -name "*.java")

EXT = /usr/local/netbeans-11.3/netbeans/platform/modules/ext
JUNIT_JARS = $(EXT)/junit-4.12.jar:$(EXT)/hamcrest-core-1.3.jar

ANT_DIR = /usr/share/ant
ANT_JARS := $(ANT_DIR)/ant-launcher-1.10.5.jar
ANT_JARS := $(ANT_JARS):$(ANT_DIR)/lib/ant.jar
ANT_JARS := $(ANT_JARS):$(ANT_DIR)/lib/ant-junit.jar
ANT_JARS := $(ANT_JARS):$(ANT_DIR)/lib/ant-junit4.jar

RUNNER = org.apache.tools.ant.taskdefs.optional.junit.JUnitTestRunner

TEST_OPTIONS = 'skipNonTests=false'
TEST_OPTIONS +=  'filtertrace=true'
TEST_OPTIONS +=  'haltOnError=false'
TEST_OPTIONS +=  'haltOnFailure=false'
TEST_OPTIONS +=  'showoutput=true'
TEST_OPTIONS +=  'outputtoformatters=true'
TEST_OPTIONS +=  'logfailedtests=true'
TEST_OPTIONS +=  'threadid=0'
TEST_OPTIONS +=  'logtestlistenerevents=false'
TEST_OPTIONS +=  'formatter=org.apache.tools.ant.taskdefs.optional.junit.BriefJUnitResultFormatter'


.PHONY : build compile-src compile-tests run run-tests clean

compile-src: build/classes
	javac -cp build/classes -d build/classes $(SOURCES)

compile-tests: compile-src build/test/classes
	javac -cp build/classes:build/test/classes:$(JUNIT_JARS) -d build/test/classes $(TESTS)

dist: compile-src
	$(RM) -rf dist
	mkdir dist
	jar cef $(main_class) dist/$(project_name).jar -C build/classes .

run: compile-src build/classes
	java -cp build/classes $(main_calls)

run-tests: compile-tests
	for t in ${test_classes} ; do \
		java -cp $(ANT_JARS):build/classes:build/test/classes:$(JUNIT_JARS) -ea $(RUNNER) $$t $(TEST_OPTIONS) ; \
    done

build/classes build/test/classes: 
	mkdir -p $@

clean: 
	$(RM) $$(find . -name "*~")
	$(RM) -r build/*

