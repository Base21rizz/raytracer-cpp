import struct
import sys
import zlib
from pathlib import Path


def make_chunk(chunk_type: bytes, data: bytes) -> bytes:
    crc = zlib.crc32(chunk_type + data) & 0xFFFFFFFF
    return struct.pack("!I", len(data)) + chunk_type + data + struct.pack("!I", crc)


def read_ppm_text(path: Path) -> str:
    raw = path.read_bytes()
    if raw.startswith((b"\xff\xfe", b"\xfe\xff")):
        return raw.decode("utf-16")
    if raw.startswith(b"\xef\xbb\xbf"):
        return raw.decode("utf-8-sig")
    return raw.decode("ascii")


def ppm_to_png(input_path: Path, output_path: Path) -> None:
    tokens: list[str] = []
    for line in read_ppm_text(input_path).splitlines():
        line = line.split("#", 1)[0]
        if line:
            tokens.extend(line.split())

    if len(tokens) < 4 or tokens[0] != "P3":
        raise ValueError(f"{input_path} is not a valid ASCII P3 PPM file.")

    width, height, maxval = int(tokens[1]), int(tokens[2]), int(tokens[3])
    expected = width * height * 3
    values = tokens[4:]

    if len(values) != expected:
        raise ValueError(
            f"Expected {expected} channel values, got {len(values)}.")

    if maxval == 255:
        pixels = bytes(map(int, values))
    else:
        pixels = bytes(round(int(v) * 255 / maxval) for v in values)

    row_bytes = width * 3
    raw = bytearray()
    for y in range(height):
        raw.append(0)  # PNG filter type 0 (None)
        start = y * row_bytes
        raw.extend(pixels[start: start + row_bytes])

    ihdr = struct.pack("!IIBBBBB", width, height, 8, 2, 0, 0, 0)
    png_data = (
        b"\x89PNG\r\n\x1a\n"
        + make_chunk(b"IHDR", ihdr)
        + make_chunk(b"IDAT", zlib.compress(bytes(raw), level=9))
        + make_chunk(b"IEND", b"")
    )

    output_path.write_bytes(png_data)
    print(f"Saved {output_path} ({width}x{height})")


if __name__ == "__main__":
    src = Path(sys.argv[1]) if len(sys.argv) > 1 else Path("image.ppm")
    dst = Path(sys.argv[2]) if len(sys.argv) > 2 else Path("render.png")
    ppm_to_png(src, dst)
