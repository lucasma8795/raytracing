import pandas as pd
import re


def main():
    with open("./html_colours.csv", 'r') as fo:
        df = pd.read_csv(fo)
    
    for idx, row in df.iterrows():
        # https://stackoverflow.com/questions/1175208/elegant-python-function-to-convert-camelcase-to-snake-case
        name = re.sub(r'(?<!^)(?=[A-Z])', '_', row.Colour).upper()

        r, g, b = map(float, row.RGB.split(' '))

        print(f"constexpr glm::vec3 {name}{{{r/256:.4f}f, {g/256:.4f}f, {b/256:.4f}f}};")


if __name__ == "__main__":
    main()