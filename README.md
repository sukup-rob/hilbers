
----------
# en
- two applications written in C for the class "CNC Machining – Robots in Artistic Practice" at VUT FIT Brno
- `txtHilberts.exe` prompts the user for a number of iterations. it creates/truncates `output.txt` and writes the path in using following logic:

| u |     UP |
| r |  RIGHT |
| d |   DOWN |
| l |   LEFT |
| s |   STOP |

(`STOP` should not appear in `output.txt` - it is a legacy value.)
- `svgMaker.exe` reads `output.txt` and reinterprets it as a .svg into `output.svg`.

NOTE:
> my laptop cannot handle more than 11 iterations.
> if you decide to look for your machines limit, heres a tip: 
> `SHIFT + C` forces most console applications to stop.

NOTE 2:
> `svgMaker.exe` WILL generate a .svg out of other paths written in the "urdls" system, but...
1) first point will always be placed at [0,0]
2) in most cases, you will need to open `output.svg` afterwards and tweak the viewing window manually.
3) i'm not sure if theres a way to make paths going into negative space work - havent tested it or anything.


----------
# cs
- dva C programy napsané pro "CNC obrábění – Roboti v umělecké praxi" VUT FIT Brno
- `txtHilberts.exe` si po spuštění vyžádá počet iterací. vytvoří/vymaže `output.txt` a zapíše do něj cestu pomocí následující logiky:

| u |     UP |
| r |  RIGHT |
| d |   DOWN |
| l |   LEFT |
| s |   STOP |

(STOP by se v `output.txt` nemělo objevit, ale je součástí kódu, takže ho nechávám přiložený.)
- `svgMaker.exe` přečte `output.txt` a přeformátuje ho do jako .svg do `output.svg`.

POZNÁMKA:
> můj počítač nezvládne víc než 11 iterací. 
> jestli budete zkoušet limity vlastního stroje, zde je tip: 
> `SHIFT + C` vynutí konec většiny konzolových aplikací.

POZNÁMKA 2:
> `svgMaker.exe` může kreslit do .svg i dráhy které nebyly vytvořeny přes `txtHilbert.exe`, ale...
1) první bod bude vždy na [0,0].
2) ve většině případů bude nutné manuálně upravit velikost zobrazení `output.svg`.
3) není mi jasné, jestli vůbec existuje způsob, jak zobrazit body v negativním prostoru - o svg toho tolik nevím 💔


---------
```
Robin Sukup
sukup.rob@proton.me
29. 3. 2024
```