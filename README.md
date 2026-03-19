# CPU Scheduling Algorithms - C++

## 👥 Autores

* Santiago Grande
* Emily Bonilla
* Santiago Figueroa

---

## 📌 Descripción

Este proyecto implementa los siguientes algoritmos de planificación de CPU:

* FCFS (First Come First Serve)
* SJF (Shortest Job First)
* RR (Round Robin)
* PSJF (Preemptive Shortest Job First)

El programa lee procesos desde un archivo y simula la ejecución mostrando:

* Timeline de ejecución
* Métricas: CT, TAT, WT, RT
* Orden de ejecución

---

## 📂 Formato del archivo de entrada

Cada línea representa un proceso:

```
ID;BurstTime;ArrivalTime;QueueID;Priority
```

Ejemplo:

```
A;5;0;1;1
B;3;1;1;2
```

Líneas que comienzan con `#` son ignoradas.

---

## ⚙️ Compilación

```
g++ scheduling.cpp -o sc
```

---

## ▶️ Ejecución

### FCFS

```
./sc test1.txt FCFS
```

### SJF

```
./sc test1.txt SJF
```

### Round Robin

```
./sc test2.txt RR 2
```

(El último parámetro es el quantum)

### PSJF

```
./sc test3.txt PSJF
```

---

## 📊 Salida

El programa muestra:

### Timeline

```
t=0 -> A -> t=5
t=5 -> B -> t=8
```

### Tabla de resultados

```
ID  AT  BT  CT  TAT  WT  RT
A   0   5   5   5    0   0
```

---

## 🐳 Uso con Docker

Si usas la imagen `so-tools`:

```
docker run -it -v $(pwd):/app so-tools
cd /app
g++ scheduling.cpp -o sc
./sc test1.txt FCFS
```
---

## 📎 Archivos incluidos

* `scheduling.cpp`
* `test1.txt`
* `test2.txt`
* `test3.txt`

---

