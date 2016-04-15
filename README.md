**GATB** - The **G**enome **A**nalysis **T**oolbox with de-**B**ruijn graph

| **Linux** | **Mac OSX** |
|-----------|-------------|
[![Build Status](https://ci.inria.fr/gatb-core/view/GATB-CORE/job/test-suite-debian7-64bits-gcc-4.7/badge/icon)](https://ci.inria.fr/gatb-core/view/GATB-CORE/job/test-suite-debian7-64bits-gcc-4.7/) | [![Build Status](https://ci.inria.fr/gatb-core/view/GATB-CORE/job/test-suite-macos-10.9.5-gcc-4.2.1/badge/icon)](https://ci.inria.fr/gatb-core/view/GATB-CORE/job/test-suite-macos-10.9.5-gcc-4.2.1/)

[![License](http://img.shields.io/:license-affero-blue.svg)](http://www.gnu.org/licenses/agpl-3.0.en.html)

--------------------------------------------------------------------------------
# What is GATB ?

GATB is made of two master projects: 

* The **GATB-CORE project** provides a set of highly efficient algorithms to analyse NGS data sets. These 
methods enable the analysis of data sets of any size on multi-core desktop computers, including very 
huge amount of reads data coming from any kind of organisms such as bacteria, plants, animals and 
even complex samples (e.g. metagenomes). Read more about GATB at <a href="https://project.inria.fr/gatb/">https://project.inria.fr/gatb</a>.
 
* The **GATB-TOOLS project** contains a set of ready-to-use softwares relying on GATB-CORE algorithms. You can have a look at available tools at <a href="https://project.inria.fr/gatb/software/">https://project.inria.fr/gatb/software</a>.

--------------------------------------------------------------------------------
# What is GATB-CORE ?

GATB-CORE is a high-performance and low memory footprint C++ library.

GATB-Core natively provides the following operations:

* Reads handling: 	
 * FASTA/FASTQ parsing
 * Parallel iteration of sequences

* K-mer: 	

 * K-mer counting
 * Minimizer computation of k-mers, partitioning of datasets by minimizers
 * Bloom data structure of k-mers
 * Hash table of k-mers
 * Minimal perfect hash function of k-mers
 * Arbitrarily large k-mers representations

* de Bruijn graph: 	

 * graph construction
 * graph traversal operations (contigs, unitigs)
 * graph simplifications for assembly (tip removal, bulge removal)

By itself GATB-CORE is not an NGS data analysis tool. However, it can be 
used to create such tools; see below section called 'How to quickly create a project based on gatb-core ?'.

They already exist a set of ready-to-use tools relying on GATB-CORE library: see [https://project.inria.fr/gatb/software/](https://project.inria.fr/gatb/software/)

# License

GATB is free software; you can redistribute it and/or modify it under the Affero GPL v3 
license. See http://www.gnu.org/licenses/agpl-3.0.en.html

# Project content

All the needed material of GATB-CORE is contained in the current directory in order to 
generate the wanted artifacts:  

* dynamic and static libraries holding the services component

* unit tests of the component

# Compiling GATB-CORE

Since the compilation is based on CMake (release 2.6+), a common way to build all the artifacts is:

	cd gatb-core/gatb-core
	mkdir build ; cd build ; cmake .. ; make
	
Unit tests (requires cppunit) can also be executed to check the integrity of the library on your system:

     cd gatb-core/gatb-core/build
     make test

More about GATB-CORE code compiling instruction is available [here](http://gatb-core.gforge.inria.fr/doc/api/compilation.html).

# Reading documentation

API documentation is available [here](http://gatb-core.gforge.inria.fr/doc/api/).

Nevertheless, you can create a local copy of the documentation as follows (we suppose you already compiled the c++ code, see above; requires 'doxygen'):

     cd gatb-core/gatb-core/build
     make doc

Documentation is then available in _build/html/index.html_


# kmer default sizes

By default, the library is compiled for supporting 4 ranges of kmers : 

* k1 : for kmerSize < k1  (default value 32)         
* k2 : for k1 <= kmerSize < k2 (default value 64)
* k3 : for k2 <= kmerSize < k3 (default value 96)
* k4 : for k3 <= kmerSize < k4 (default value 128)

You can customize these values through cmake, provided they rebuild the project from scratch. For instance:

    rm -Rf build; mkdir build ; cd build ; cmake -DKSIZE_LIST="64 96 128 162" ..

Tools may set a default kmer lists in their CMakeFiles.txt, as such (see for instance Minia):

    list (APPEND KSIZE_DEFAULT_LIST  32   64   96  128  160  192  224  256)

	
--------------------------------------------------------------------------------
# Dependencies

The following third parties should be already installed:

* cmake (mandatory)
* doxygen
* cppunit

--------------------------------------------------------------------------------
# Directory content

* __README__:                  this file

* __CMakeList.txt__:           global cmake file

* __doc__:                 
    * __design__      design documentation for the component
    * __doxygen__     pages for doxygen

* __examples__:       snippets showing how to use the library                 

* __src__:            source code for the component

* __test__:           tests directory
    * __src__         source code for unit tests
    * __db__          FASTA databases for unit tests

* __thirdparty__:    third parties    

--------------------------------------------------------------------------------
# Details for 'src' directory content

It contains several sub directories, each one corresponding to one software package.

A package may be composed of sub packages; the directory hierarchy should represent
this packages tree structure.

For one atomic package (or sub package), we should have:

* directory 'api'       API of the package  

* directory 'impl'      several implementations of the API

--------------------------------------------------------------------------------
# How to quickly create a project based on GATB-CORE ?

You use GATB-CORE by creating a new tool project, with the following script:

    sh scripts/NewProject/NewProject.sh  -d directory -n toolName

where 'directory' is the directory where the project will be created and 'toolName' is the name of the project.
The script will automatically creates the full path directory/toolName to deploy a self-contained tool.
 
By default, the following part will be included in the project:
    * a CMakeLists.txt file used for building the project
    * a 'tools' directory holding a default source code using GATB-Core
    * a 'scripts' directory holding a script to automatically package the tool
    * an optional 'thirdparty' directory holding the gatb-core resources

The 'thirdparty' directory is only available for tool created outside the GATB-Tools repository.
Tools located within GATB-Tools rely on a common GATB-CORE sub-module already available in this repository.

The directory where the project is created has no link to any external resources. You can therefore
move it anywhere you want.

Such a project can be a start for building applications based on GATB-CORE. 

More on creating a new GATB-Core based project: [http://gatb-core.gforge.inria.fr/doc/api/new_project.html](http://gatb-core.gforge.inria.fr/doc/api/new_project.html)

----------------------------------------------------------------------------------
# Notes for GATB-core developers

To compile in debug mode, type.

    mkdir build ; cd build && cmake -Ddebug=1 .. && make -j


To run unit tests:

* compile using the command above (-Ddebug=1 isn't necessary) 
* then type:

        bin/gatb-core-cppunit

One may set the environment variable CPPUNIT_VERBOSE to 1 to known which tests pass.

The gatb-core-cppunit command may also take as argument the categories of tests that show up in the verbose output, e.g. 'bin/gatb-core-cppunit TestBank'.


#Contact

To contact a developer, request help, etc: https://gatb.inria.fr/contact/