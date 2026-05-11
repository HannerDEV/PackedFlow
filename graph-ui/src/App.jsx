import React, { useCallback, useState } from "react";
import ReactFlow, {
  addEdge,
  Background,
  Controls,
  useEdgesState,
  useNodesState,
} from "reactflow";
import "reactflow/dist/style.css";

let id = 1;
const getId = () => `${id++}`;

export default function GraphEditor() {
  const [nodes, setNodes, onNodesChange] = useNodesState([]);
  const [edges, setEdges, onEdgesChange] = useEdgesState([]);
  const [weight, setWeight] = useState(1);

  const [originNode, setOriginNode] = useState("");
  const [destinationNode, setDestinationNode] = useState("");

  // Crear nodo
  const addNode = () => {
    const newNode = {
      id: getId(),
      data: { label: `Nodo ${nodes.length}` },
      position: {
        x: Math.random() * 400,
        y: Math.random() * 400,
      },
    };
    setNodes((nds) => nds.concat(newNode));
  };

  // Conexión dirigida con peso
  const onConnect = useCallback(
    (params) => {
      const newEdge = {
        ...params,
        label: String(weight),
        data: { weight: Number(weight) },
        markerEnd: { type: "arrowclosed" },
      };
      setEdges((eds) => addEdge(newEdge, eds));
    },
    [weight, setEdges]
  );

  // Exportar grafo (peso)
  const exportCSV = () => {
    let csv = "NodoInicial,NodoFinal,PesoArista\n";

    edges.forEach((e) => {
      csv += `${e.source},${e.target},${e.data?.weight ?? e.label}\n`;
    });

    const blob = new Blob([csv], { type: "text/csv" });
    const url = URL.createObjectURL(blob);

    const a = document.createElement("a");
    a.href = url;
    a.download = "grafo.csv";
    a.click();

    URL.revokeObjectURL(url);
  };

  // Exportar el par seleccionado a Direccion.csv
  const exportDireccionCSV = () => {
    if (originNode === "" || destinationNode === "") {
      alert("Selecciona un nodo origen y un nodo destino.");
      return;
    }

    const csv = `NodoOrigen,NodoDestino\n${originNode},${destinationNode}\n`;

    const blob = new Blob([csv], { type: "text/csv" });
    const url = URL.createObjectURL(blob);

    const a = document.createElement("a");
    a.href = url;
    a.download = "Direccion.csv";
    a.click();

    URL.revokeObjectURL(url);
  };

  return (
    <div style={{ height: "100vh" }}>
      <div style={{ padding: 10, display: "flex", gap: 10, flexWrap: "wrap" }}>
        <button onClick={addNode}>Agregar nodo</button>

        <input
          type="number"
          value={weight}
          onChange={(e) => setWeight(e.target.value)}
          style={{ width: 80 }}
          placeholder="Peso"
        />

        <button onClick={exportCSV}>Exportar Grafo CSV</button>

        <select
          value={originNode}
          onChange={(e) => setOriginNode(e.target.value)}
        >
          <option value="">Nodo origen</option>
          {nodes.map((node) => (
            <option key={node.id} value={node.id}>
              {node.data?.label ?? node.id}
            </option>
          ))}
        </select>

        <select
          value={destinationNode}
          onChange={(e) => setDestinationNode(e.target.value)}
        >
          <option value="">Nodo destino</option>
          {nodes.map((node) => (
            <option key={node.id} value={node.id}>
              {node.data?.label ?? node.id}
            </option>
          ))}
        </select>

        <button onClick={exportDireccionCSV}>Exportar Direccion CSV</button>
      </div>

      <ReactFlow
        nodes={nodes}
        edges={edges}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        onConnect={onConnect}
        fitView
      >
        <Background />
        <Controls />
      </ReactFlow>
    </div>
  );
}