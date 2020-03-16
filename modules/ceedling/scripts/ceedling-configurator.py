#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8

"""
Path configuration for Ceedling

Usage: ceedling_configurator.py <seed_filename> <output_filename> \
--test-paths=TEST_PATHS \
--support-paths=SUPPORT_PATHS \
--source-paths=SOURCE_PATHS \
--build-dir=BUILD_DIR \
[--cexception-dir=CE_DIR] \
[--unity-helpers=UNITY_HELPERS] \
--define=DEFINE

Options:
    --test-paths=TEST_PATHS, -tTEST_PATHS           Paths to search for test files
    --support-paths=SUPPORT_PATHS, -uSUPPORT_PATHS  Paths to search for support files
    --source-paths=SOURCE_PATHS, -sSOURCE_PATHS     Paths to search for source files
    --build-dir=BUILD_DIR, -bBUILD_DIR              Directory for ceedling build products
    --cexception-dir=CE_DIR, -EBUILD_DIR            Directory that will be searched for c_exception
    --define=DEFINE, -dDEFINE                       Preprocessor definitions for tests
    --unity-helpers=UNITY_HELPERS, -yUNITY_HELPERS  Cmock headers which define helper assertions
"""
import docopt

import yaml
import sys


if __name__ == "__main__":
    arguments = docopt.docopt(__doc__)
    seed_filename       = arguments['<seed_filename>']
    output_filename     = arguments['<output_filename>']

    source_paths        = arguments['--source-paths'].split(',')
    test_paths          = arguments['--test-paths'].split(',')
    support_paths       = arguments['--support-paths'].split(',')
    build_dir           = arguments['--build-dir']
    cexception_dir      = arguments['--cexception-dir']
    unity_helpers       = arguments['--unity-helpers']

    raw_define          = arguments['--define']
    define              = raw_define.split(',') if raw_define else []
    with open(seed_filename, 'r') as project_stream:
        project_data = yaml.load(project_stream)
        project_data[':paths'] = {}
        project_data[':paths'][':source'] = source_paths
        project_data[':paths'][':test'] = test_paths
        project_data[':paths'][':support'] = support_paths
        project_data[':defines'][':common'].extend(define)
        project_data[':project'][':build_root'] = build_dir
        if cexception_dir:
            project_data[':cexception_path'] = cexception_dir
            project_data[':project'][':use_exceptions'] = True
        if unity_helpers:
            unity_helpers = unity_helpers.split(',')
            project_data[':cmock'][':unity_helper'] = unity_helpers
        with open(output_filename, 'w') as output_file:
            output_file.write(yaml.dump(project_data, default_flow_style=False))
