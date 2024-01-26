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

### InfluxDB

```bash
cd influx-db
docker-compose up -d --build
```


### Mosquito

```bash
cd mosquito
docker-compose up -d --build
```

### Grafana

```bash
cd grafana
docker-compose up -d --build
```