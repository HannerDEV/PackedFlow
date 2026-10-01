import gzip
import re
import csv

osm = "./osm/barbosa.osm.gz"
nodos_archive = "./csv/nodos.csv"


with gzip.open(osm, "rt", encoding="utf-8") as osm, \
        open(nodos_archive, "w", newline="", encoding="utf-8") as salida:

    escritor = csv.writer(salida)

    # Encabezado
    escritor.writerow(["ID", "Latitud", "Longitud", "Elevacion"])

    for linea in osm:

        if "<node " in linea:

            id_nodo = re.search(r'id="([^"]+)"', linea).group(1)
            latitud = re.search(r'lat="([^"]+)"', linea).group(1)
            longitud = re.search(r'lon="([^"]+)"', linea).group(1)

            elevacion = 0

            escritor.writerow([
                id_nodo,
                latitud,
                longitud,
                elevacion
            ])