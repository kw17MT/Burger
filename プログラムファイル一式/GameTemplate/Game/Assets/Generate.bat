@echo off
rem �ϐ��̑����W�J���I�t
setlocal enabledelayedexpansion

echo ���W�������t�@�C���̊g���q���w�肵�Ă��������B
set /p extension=��

rem �o�͐�t�@�C���p�X�̐ݒ�
set outputpath=!extension!Assets.h

cd ..

findstr pragma %outputpath% > nul
if %ERRORLEVEL%==1 (
	echo ����āA�t�@�C����V�K�쐬���܂��B
	echo #pragma once > %outputpath%
	echo. >> %outputpath%
	echo. >> %outputpath%
)

cd Assets

rem .tkm�Ƃ����t�@�C��������
for /f "usebackq" %%a in (`dir /s /b *.!extension!`) do (
	call :DoExtract %%a
)

echo �I�����܂����B

pause

exit

:DoExtract
		rem Game�܂ňړ�
		cd ..
		rem Game�܂ł̃t�@�C���p�X���擾
		set directorypath=%cd%\
		rem Assets�ɖ߂�
		cd Assets
		rem ���f���̃p�X�i�[
		set filepath=%1
		rem ���f���̃p�X����Game\�܂ł̃p�X���폜
		set filepath=!filepath:%directorypath%=!
		
		rem \����/�ɕϊ�
		set filepath=!filepath:\=/!
		
		rem �����̂���Result.txt������ꏊ�ɍs��
		cd ..
		rem ���ɏ������܂�Ă��邩���� .������Ɛ��K�\���ɂȂ�̂Ŋg���q��4�����������Č���
		findstr !filepath:~0,-4! %outputpath% > nul
		
		rem �������܂�ĂȂ�������
		if %ERRORLEVEL%==1 (
			:preName
			rem �p�X�ɂ��閼�O�����
			echo !filepath!�@�ɂ��閼�O����͂��Ă��������B
			set /p name=��
			findstr !name! %outputpath% > nul
			if !ERRORLEVEL!==1 (
			rem ��������
			echo const char* !name! = L"!filepath!"; >> %outputpath%
			) else (
				echo ���Ɏg���Ă���p�X�ł��B
				goto preName
			)
		)
		
		rem Result.txt���������ꏊ����Assets�܂Ŗ߂��Ă���
		cd Assets
		rem �T�u���[�`�����甲����
		exit /b
		
		
		
		
		
		rem made by Junou Nishikiori