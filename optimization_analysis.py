import pathlib
from ssl import get_default_verify_paths
import pandas
import difflib


def get_main(folder_name: str):
    for path in (pathlib.Path().cwd() / folder_name).glob("*.txt"):
        if (
            "results" not in path.stem
            and "trimmed" not in path.stem
            and "diff" not in path.stem
        ):
            with path.open("r") as file:
                for line in file:
                    if line.rstrip().endswith("<main>:"):
                        with (path.parent / f"{path.stem}_trimmed.txt").open(
                            "w"
                        ) as out:
                            out.write(line)
                            line = file.readline()
                            while line.startswith("    "):
                                out.write(line)
                                line = file.readline()


def get_diff(folder_name: str, basename: str):
    with (pathlib.Path().cwd() / folder_name / basename).open("r") as b:
        base = b.read().split("\n")

    for path in (pathlib.Path().cwd() / folder_name).glob("*_trimmed.txt"):
        if "results" not in path.stem:
            with path.open("r") as file:
                snippet = file.read().split("\n")
            with (path.parent / f"{path.stem.strip('_trimmed')}_diff.txt").open(
                "w"
            ) as out:
                diffs = list(difflib.unified_diff(base, snippet, lineterm="\n"))
                files = f"{pathlib.Path(basename).stem.strip('_trimmed')}:{path.stem.strip('_trimmed')} diffs"
                print(f"{files:35} - {len(diffs)}"
                )
                if len(diffs):
                    for line in diffs:
                        out.write(f"{line}\n")


def get_results(filename: str = "optimization_flags/results.txt"):
    data = {}
    with (pathlib.Path().cwd() / filename).open("r") as file:
        for line in file:
            if line.startswith("-"):
                key = line.strip()
                data[key] = [None, None, None]
            elif line.startswith("Loading") and ":" in line:
                data[key][0] = int(line.strip().split(":")[-1][:-2])
            elif line.startswith("Worse") and ":" in line:
                data[key][1] = int(line.strip().split(":")[-1][:-2])
            elif line.startswith("Better") and ":" in line:
                data[key][2] = int(line.strip().split(":")[-1][:-2])
    results = pandas.DataFrame.from_dict(
        data,
        orient="index",
        columns=["loading", "branching", "no_branching"],
    )
    return results


if __name__ == "__main__":
    get_main("optimization_flags")
    get_diff("optimization_flags", "O0_trimmed.txt")

    results = get_results()
    print(results[["branching", "no_branching"]].mean())
