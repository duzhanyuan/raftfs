## Create Docker container for function testing

### Software 

Docker

[blockade](https://github.com/dcm-oss/blockade) 

### Generate server container

```
cd docker && ./create_run_container.sh
```

### Launch 3-node cluster

```
cd docker/blockade
sudo blockade up
```
