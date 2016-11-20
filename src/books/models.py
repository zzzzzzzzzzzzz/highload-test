# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models

# Create your models here.


class Book(models.Model):
    title = models.CharField(
        u'Название',
        max_length=128,
        default=u'Книга без названия'
    )
    content = models.TextField(
        u'Описание',
        default='Бла бла бла',
        null=True
    )

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name = u'Книга'
        verbose_name_plural = u'Книги'
