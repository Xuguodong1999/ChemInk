::
::  ����һ������ű�
::  ����֮ǰ��ȷ�ϣ�
::  1��./ChemInk/thrid_party�µ��ļ���֯����./ChemInk/thrid_party/Structure.md
::  2���� QT_MSVC_2017>=5.12.2 ��binĿ¼���뻷������
::  3���� vs ��չ������qt_vs_tools��Ĭ��qt�汾ΪQT_msvc2017
::  4���� vs x64 native tools ����������������ű�
msbuild ChemInk.sln /p:Configuration=Release -m
::  5���� ./x64/Release�ļ����³��ֿ�ִ���ļ�
::  6���� ./ChemInk/data �ļ��и��Ƶ���ִ���ļ�����Ŀ¼
::  ����ΪʲôҪ�ýű��أ�����IDE���㣨x
::