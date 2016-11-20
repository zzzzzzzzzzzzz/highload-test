# highload-test
Streess test of Django ORM and MySQL (InnoDB).

Используется Django Rest Framework (т.е. с базой общается Django ORM), на раздачу статики настроен Nginx (порт 80), на более сложные запросы gunicorn (4 воркера). База mysql, движок InnoDB.
Для генерации данных используется программа на C (см. папку booksgen).

**Отчёт находится в папке report. См. файл Ex2.html**
