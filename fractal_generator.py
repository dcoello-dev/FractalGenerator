import json
import argparse

import numpy as np
from PIL import Image

import Fractal

def color(rgbint):
    return (rgbint // 256 // 256 % 256, rgbint // 256 % 256, rgbint % 256)

parser = argparse.ArgumentParser()

parser.add_argument(
    '-wd', '--width',
    default=512,
    help="image width")

parser.add_argument(
    '-he', '--height',
    default=512,
    help="image height")

parser.add_argument(
    '-d', '--depth',
    default=512,
    help="image depth")

parser.add_argument(
    '-o', '--output',
    default="fractal.png",
    help="output image")

args = parser.parse_args()

if __name__ == "__main__":
    buffer = json.loads(Fractal.calculate(int(args.width), int(args.height), int(args.depth)))["mat"]

    data = np.zeros((int(args.width), int(args.height), 3), dtype=np.uint8)

    for i in range(0, len(buffer)):
        data[int(i / int(args.width)), int(i % int(args.width))] = color(buffer[i] * 100)

    img = Image.fromarray(data, 'RGB')
    img.save(args.output)