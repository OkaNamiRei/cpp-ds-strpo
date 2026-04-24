# Docker demo for СТРПО-7

Команды:

```bash
docker build -t ds_strpo_cat docker/
docker run --rm ds_strpo_cat
docker run --rm ds_strpo_cat "meow from container"
```

Что объяснять:
- `FROM` задаёт базовый образ.
- `RUN` выполняется во время сборки образа.
- `WORKDIR` задаёт рабочую папку внутри образа.
- `COPY` переносит файл в образ.
- `CMD` задаёт команду по умолчанию при запуске контейнера.


## Команды для защиты
```powershell
docker --version
docker run hello-world
docker run -it ubuntu bash
docker build -t strpo7-ascii-cat .
docker run --rm strpo7-ascii-cat
docker images
docker ps -a
```
