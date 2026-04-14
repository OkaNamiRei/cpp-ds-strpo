# 16. SSH и первый push: пошагово

## 1. Сгенерировать ключ

### Windows PowerShell / Git Bash / WSL
```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

Просто жми Enter на пути по умолчанию. Если спросит passphrase, можно оставить пустым или задать пароль.

## 2. Посмотреть публичный ключ

```bash
cat ~/.ssh/id_ed25519.pub
```

На Windows в PowerShell путь может быть таким:

```powershell
type $env:USERPROFILE\.ssh\id_ed25519.pub
```

## 3. Добавить ключ в GitHub

GitHub → Settings → SSH and GPG keys → New SSH key → вставить содержимое `id_ed25519.pub`.

## 4. Проверить соединение

```bash
ssh -T git@github.com
```

Ожидаемое поведение: GitHub поздоровается и скажет, что shell-доступ не предоставляется.

## 5. Создать приватный репозиторий

На GitHub создать новый `Private` repo без README.

## 6. Первый push

```bash
git init
git branch -M main
git add .
git commit -m "init: add combined ds/strpo project"
git remote add origin git@github.com:YOUR_LOGIN/YOUR_REPO.git
git push -u origin main
```

## 7. Создать dev и feature-ветку

```bash
git switch -c dev
git push -u origin dev
git switch -c feature/example
```

## 8. Что говорить на защите

- SSH не обязателен по переписке, но это «правильный путь».
- Репозиторий приватный.
- В main напрямую не коммитим.
- Работа идёт через dev и feature-ветки.
