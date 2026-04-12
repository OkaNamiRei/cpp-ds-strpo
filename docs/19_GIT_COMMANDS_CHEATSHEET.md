# 19. Короткая шпаргалка по Git

```bash
git status
git add .
git commit -m "message"
git push
git pull
git branch
git switch dev
git switch -c feature/name
git log --oneline --graph --decorate --all
```

## Типовой цикл

```bash
git switch dev
git switch -c feature/sd3-workerdb
# работа
git add .
git commit -m "feat(sd3): add worker db and iterator"
git push -u origin feature/sd3-workerdb
```
