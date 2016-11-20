# -*- coding: utf-8 -*-
# Generated by Django 1.10.3 on 2016-11-11 14:55
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Book',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(default='\u041a\u043d\u0438\u0433\u0430 \u0431\u0435\u0437 \u043d\u0430\u0437\u0432\u0430\u043d\u0438\u044f', max_length=128, verbose_name='\u041d\u0430\u0437\u0432\u0430\u043d\u0438\u0435')),
                ('content', models.TextField(default='\u0411\u043b\u0430 \u0431\u043b\u0430 \u0431\u043b\u0430', null=True, verbose_name='\u041e\u043f\u0438\u0441\u0430\u043d\u0438\u0435')),
                ('created_at', models.DateTimeField(auto_now_add=True, verbose_name='\u0414\u0430\u0442\u0430 \u0434\u043e\u0431\u0430\u0432\u043b\u0435\u043d\u0438\u044f')),
            ],
            options={
                'ordering': ['-created_at'],
                'verbose_name': '\u041a\u043d\u0438\u0433\u0430',
                'verbose_name_plural': '\u041a\u043d\u0438\u0433\u0438',
            },
        ),
    ]