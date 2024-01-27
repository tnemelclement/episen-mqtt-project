# MQTT Project

## Get started

1. Create the network `mqtt-project-network`
2. Run `node-red` 
3. Run `grafana`
4. Run `influx-db`
5. Run `mosquito`

### Network 

```bash
docker network create mqtt-project-network
```

### Node Red

```bash
cd node-red
docker-compose up -d --build
```

Available on `localhost:1880`.

### InfluxDB

```bash
cd influx-db
docker-compose up -d --build
```

Available on `localhost:8086`.


### Mosquito

```bash
cd mosquito
docker-compose up -d --build
```

- `localhost:1883` for MQTT.
- `localhost:8001` for WebSocket.

### Grafana

```bash
cd grafana
docker-compose up -d --build
```

Available on `localhost:3000`.
