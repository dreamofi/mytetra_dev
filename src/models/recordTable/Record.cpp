#include "main.h"
#include "Record.h"


Record::Record()
{
  liteFlag=true; // По-умолчанию объект легкий
}


Record::~Record()
{

}


bool Record::isNull()
{
  // Заполненная запись не может содержать пустые свойства
  if(fieldList.count()==0)
    return true;
  else
    return false;
}


bool Record::isLite()
{
  return liteFlag;
}


void Record::switchToLite()
{
  pictureFiles.clear();
  attachFiles.clear();

  liteFlag=true;
}


void Record::switchToFat()
{
  // Переключение возможно только из легкого состояния
  if(liteFlag!=true || pictureFiles.count()>0 || attachFiles.count()>0)
  {
    critical_error("Unavailable switching record object to fat state. "+getIdAndNameAsString());
    return;
  }

  liteFlag=false;
}


QString Record::getIdAndNameAsString()
{
  QString id, name;

  if(fieldList.contains("id"))
    id=fieldList["id"];

  if(fieldList.contains("name"))
    name=fieldList["name"];

  return "Record ID: "+id+" Name: "+name;
}


// Тажелые свойства устанавливаются и берутся через геттеры и сеттеры
QMap<QString, QByteArray> Record::getPictureFiles()
{
  // У легкого объекта невозможно запросить картики, если так происходит - это ошибка вызывающей логики
  if(liteFlag==true)
    critical_error("Cant get picture files from lite record object"+getIdAndNameAsString());

  return pictureFiles;
}


// todo: Переделать на копирование по ссылке
void Record::setPictureFiles(QMap<QString, QByteArray> iPictureFiles)
{
  // Легкому объекту невозможно установить картики, если так происходит - это ошибка вызывающей логики
  if(liteFlag==true)
    critical_error("Cant set picture files for lite record object"+getIdAndNameAsString());

  pictureFiles=iPictureFiles;
}


QMap<QString, QByteArray> Record::getAttachFiles()
{
  // У легкого объекта невозможно запросить приаттаченные файлы, если так происходит - это ошибка вызывающей логики
  if(liteFlag==true)
    critical_error("Cant get attach files from lite record object"+getIdAndNameAsString());

  return pictureFiles;
}


// todo: Переделать на копирование по ссылке
void Record::setAttachFiles(QMap<QString, QByteArray> iAttachFiles)
{
  // Легкому объекту невозможно установить картики, если так происходит - это ошибка вызывающей логики
  if(liteFlag==true)
    critical_error("Cant set attach files for lite record object"+getIdAndNameAsString());

  attachFiles=iAttachFiles;
}
