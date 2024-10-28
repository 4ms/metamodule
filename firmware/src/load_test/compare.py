#!/usr/bin/env python3

import argparse
import logging
import csv

def process_file(filename):
    r = {}
    testnames = []

    with open(filename, "r") as file:
        dictreader = csv.DictReader(file, delimiter=',', quotechar='"')
        testnames = [n.strip() for n in dictreader.fieldnames[1:-1]]

    with open(filename, "r") as file:
        logging.info(f"Processing {filename}")
        reader = csv.reader(file, delimiter=',', quotechar='"')
        skipFirstRow = True
        for row in reader:
            if skipFirstRow:
                skipFirstRow = False
            else:
                r[row[0]] = [float(x) for x in row[1:-1]]

    return r, testnames


def find_differences(ref, test, tol):
    return [(test[idx] - ref[idx], idx) for idx in range(len(ref)) if abs(test[idx] - ref[idx]) > tol]

if __name__ == "__main__":
    parser = argparse.ArgumentParser("Compare two cpu load test result CSV files")
    parser.add_argument("--ref", dest="reffile", help="Reference csv file")
    parser.add_argument("--new", dest="newfile", help="New test csv file")
    parser.add_argument("--result", dest="resultfile", help="Where to write results")
    parser.add_argument("--tol", dest="tol", default=0.02, type=float, help="Tolerance: ignore differences equal or below to this")
    parser.add_argument("--brand", dest="onlybrand", help="Compare only specific brand")
    parser.add_argument("--module", dest="onlymodule", help="Compare only specific module (Brand:Module format)")
    parser.add_argument("-v", dest="verbose", help="Verbose logging", action="store_true")
    args = parser.parse_args()

    logger = logging
    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)
    else:
        logging.basicConfig(level=logging.INFO)

    ref, testnames = process_file(args.reffile)
    new, newtestnames = process_file(args.newfile)

    not_found = []
    changes = {}
    for module, refload in ref.items():
        if args.onlymodule:
            if module != args.onlymodule:
                continue
        if args.onlybrand:
            if not module.startswith(args.onlybrand):
                continue
        if module in new.keys():
            testload = new[module][:len(refload)]
            logging.debug(module)
            logging.debug(f"Ref: {refload}")
            logging.debug(f"New: {testload}")
            diff = find_differences(refload, testload, args.tol)
            changes[module] = {}
            for d, idx in diff:
                logging.debug(f"{module}: {testnames[idx]} {d * 100}")
                changes[module][testnames[idx]] = float(d)

        else:
            not_found.append(module)
            print(f"Not found in new test results: {module}")

    collated = []
    for module, results in changes.items():
        for testname, diff in results.items():
            logging.info(f"{module},{testname},{'+' if diff > 0 else ''}{round(diff * 100, 1)}%")
            collated.append([module, testname, round(diff,3)])

    if args.resultfile:
        with open(args.resultfile, "w", newline='') as file:
            writer = csv.writer(file, delimiter=",", quotechar='"',quoting=csv.QUOTE_MINIMAL)
            writer.writerow(["Module", "Test", "Change"])
            for row in collated:
                writer.writerow(row)
                 

