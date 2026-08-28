"""Flatten the generated diagrams and append them for the promo image."""

from pathlib import Path

from PIL import Image

ROOT = Path(__file__).parent
base = Image.open(ROOT / "images/base-layer.png").convert("RGBA")
after = Image.open(ROOT / "images/after-n.png").convert("RGBA")
if base.size != after.size:
    raise SystemExit(f"diagram sizes differ: {base.size} vs {after.size}")

background = (36, 42, 49, 255)
divider = 12
output = Image.new("RGBA", (base.width, base.height * 2 + divider), background)
output.alpha_composite(base, (0, 0))
output.alpha_composite(after, (0, base.height + divider))
output.convert("RGB").save(ROOT / "images/after-n-promo.png", optimize=True)
