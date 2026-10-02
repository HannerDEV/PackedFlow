import gzip
import csv
import re

archivo_osm = "./osm/barbosa.osm.gz"
archivo_grafo = "./csv/grafo.csv"

with gzip.open(archivo_osm, "rt", encoding="utf-8") as osm, \
        open(archivo_grafo, "w", newline="", encoding="utf-8") as salida:

    escritor = csv.writer(salida)

    escritor.writerow(["Origen", "Destino"])

    way_nodos = []
    es_carretera = False
    sentido = "bidireccional"

    for linea in osm:

        linea = linea.strip()

        if linea.startswith("<way "):
            way_nodos = []
            es_carretera = False
            sentido = "bidireccional"

        elif "<nd ref=" in linea:
            resultado = re.search(r'ref="([^"]+)"', linea)

            if resultado:
                nodo = int(resultado.group(1))
                way_nodos.append(nodo)

        elif '<tag k="highway"' in linea:
            es_carretera = True

        elif '<tag k="oneway"' in linea:
            if 'v="yes"' in linea or 'v="1"' in linea or 'v="true"' in linea:
                sentido = "normal"

            elif 'v="-1"' in linea:
                sentido = "invertido"

        elif '<tag k="junction" v="roundabout"' in linea:
            sentido = "normal"

        elif linea == "</way>":

            if es_carretera:

                for i in range(len(way_nodos) - 1):

                    origen = way_nodos[i]
                    destino = way_nodos[i + 1]

                    if sentido == "normal":
                        escritor.writerow([origen, destino])

                    elif sentido == "invertido":
                        escritor.writerow([destino, origen])

                    else:
                        escritor.writerow([origen, destino])
                        escritor.writerow([destino, origen])