#include "PKG.h"


PKG::PKG(const QByteArray &path) : path(path) {
}


PKG::~PKG() {
	QDir().remove(package_conf);
}


bool PKG::generate_debug_package() {
	if (path.isEmpty())
		return false;
	if (path.endsWith('\\'))
		path.remove(path.size() - 1, 1);
	QByteArray title_id = path.mid(1 + path.lastIndexOf('\\'));
	if (!title_id.startsWith("BL"))
		if (!title_id.startsWith("BC"))
			if (!title_id.startsWith("NP"))
				return false;
	QByteArray part_number;
	if (title_id.contains('_')) {
		title_id = title_id.left(title_id.lastIndexOf('_'));
		part_number = ".part" + title_id.mid(1 + title_id.lastIndexOf('_'));
	}
	PARAM p(path + "\\PARAM.SFO");
	if (!p.isparam())
		return false;
	QByteArray version = p.at(PARAM::VERSION);
	QByteArray app_ver = p.at(PARAM::APP_VER);
	QByteArray target_app_ver = p.at(PARAM::CATEGORY);
	QByteArray category = p.at(PARAM::CATEGORY);
	if (version.isEmpty()) {
		version = "01.00";
		p.insert(PARAM::VERSION, version);
	}
	if (app_ver.isEmpty()) {
		app_ver = "01.00";
		p.insert(PARAM::APP_VER, app_ver);
	}
	if (target_app_ver.isEmpty() || target_app_ver != "00.01") {
		target_app_ver = "00.01";
		p.insert(PARAM::TARGET_APP_VER, target_app_ver);
	}
	if (category.isEmpty())
		return false;
	EBOOT e(path + "\\USRDIR\\EBOOT.BIN");	//	"0x00000000000000000000000000000000""Free"// || category == "HG" || category == "HD" || category == "AT") {
	if (!e.iseboot())
		return false;
	QByteArray contentid, klicensee, drmtype, contenttype, packagetype;
	contentid = e.contentid();
	if (contentid.isEmpty())
		return false;

	{
		if (category == "HD") {
			contenttype = "Game_Exec";
			set pt = "HDDGamePatch"
				set n1 = 1HDCAT
				)
				if (category == HG) {
					contenttype = Game_Exec
						set pt = HDDGamePatch
						set n1 = 1HGCAT
						)
						if (category == DG) {
							contenttype = Game_Exec
								set pt = HDDGamePatch
								set n1 = 1DGCAT
								)
								if (category == GD) {
									contenttype = Game_Data
										set pt = DiscGamePatch
										set n1 = 2PATCH
										)
										if (category == AP) {
											contenttype = Game_Exec
												set pt = HDDGamePatch
												set n1 = 1APCAT
												set title = APPPHOTO000000!ch!
												)
												if (category == AM) {
													contenttype = Game_Exec
														set pt = HDDGamePatch
														set n1 = 1AMCAT
														set title = APPMUSIC000000!ch!
														)
														if (category == AV) {
															contenttype = Game_Exec
																set pt = HDDGamePatch
																set n1 = 1AVCAT
																set title = APPVIDEO000000!ch!
																)
																if (category == AT) {
																	contenttype = Game_Exec
																		set pt = HDDGamePatch
																		set n1 = 1ATCAT
																		set title = APPTV000000000!ch!
																		)
																		if (category == 2G) {
																			set EDT = ISO.BIN.EDAT
																				contenttype = Game_Data
																				set n1 = 12GCAT
																				set title = PS2DISCINSTALL!ch!
																				)
																				if (category == 2P) {
																					set EDT = ISO.BIN.EDAT
																						contenttype = Game_Data
																						set n1 = 12PCAT
																						set title = PS2CLASSICS000!ch!
																						)
																						if (category == 2D) {
																							set EDT = ISO.BIN.EDAT
																								contenttype = Game_Data
																								set n1 = 22DCAT
																								set title = PS2EMUDATA0000!ch!
																								)
																								if (category == 1P) {
																									set EDT = ISO.BIN.EDAT
																										contenttype = Game_Data
																										set n1 = 11PCAT
																										set title = PS1CLASSICS000!ch!
																										)
																										if (category == MN) {
																											set EDT = ISO.BIN.EDAT
																												contenttype = minis
																												set n1 = 1MNCAT
																												set title = PSPMINIS000000!ch!
																												)
																												if (category == PE) {
																													set EDT = ISO.BIN.EDAT
																														contenttype = Game_Data
																														set n1 = 1PECAT
																														set title = PSPREMASTERS00!ch!
																														)
																														if (category == PP) {
																															set EDT = ISO.BIN.EDAT
																																contenttype = Game_Data
																																set n1 = 1PPCAT
																																set title = PSPGAME0000000!ch!
																																)
																														}


																													//if (category == "GD") {
																													//	contenttype = "GameData";
																													//	packagetype = "DiscGamePatch";
																													//}
																													//else if (category == "DG") {
																													//	p.insert(PARAM::APP_VER, "01.00");
																													//	contenttype = "GameExec";
																													//	packagetype = "HDDGamePatch";
																													//}
																													//else if (category == "2P") {

																													//}
																													//else if (category == "1P") {

																													//}
																													//else
																													//	return false;
																													QFile f(package_conf);
																													if (!f.open(QIODevice::WriteOnly))
																														return false;
																													QTextStream out(&f);
																													out << "ContentID = " << contentid << endl
																														<< "Klicensee = " << klicensee << endl
																														<< "DRMType = " << drmtype << endl
																														<< "InstallDirectory = " << title_id << endl
																														<< "PackageVersion = " << version << endl
																														<< "ContentType = " << contenttype << endl
																														<< "PackageType = " << packagetype << endl;
																													if (!p.close())
																														return false;
																													if (!e.close())
																														return false;
																													f.close();
																													QProcess proc;
																													proc.setProcessChannelMode(QProcess::ForwardedChannels);
																													proc.start(psn_package_npdrm, QStringList() << "-n" << "-f" << package_conf << path);
																													if (!proc.waitForStarted())
																														return false;
																													if (!proc.waitForFinished(-1))
																														return false;
																													if (proc.exitCode() != QProcess::NormalExit && proc.exitStatus() != QProcess::NormalExit)
																														return false;
																													QString pkg_name = QDir::currentPath() + '\\' + contentid + "-A" + app_ver.remove(2, 1) + "-V" + version.remove(2, 1);
																													if (!QDir().rename(pkg_name + ".pkg", pkg_name + part_number + ".pkg"))
																														return false;
																													return true;
																												}

																											{
																												@echo off
																													for / f "tokens=1,2 delims==" %%a in(config.ini) do (
																														set nm = %%a
																														if !nm != = [HotKey] goto elog
																															if !nm != = 5 set logs = %%b
																																if !nm != = 8 set flq = %%b
																																	if !flq != = 8 (set fq = 1) else (set fq = 0)
																																		if !nm != = 10 set f10 = %%b
																																			if !f10 != = 10 set cons = yes
																																				if !logs != = 5 (
																																					Echo.
																																					set logs = %cd%\log.txt
																																					echo Log on : !logs!
																																					)
																																					if !logs != = 80 (set logs = nul)
																																						)
																														: elog

																																						cd .\tools\
																																						echo.
																																						echo ATTENTION!AFTER SPLITTING THE GAME MIGHT NOT WORK!
																																						echo.
																																						set src = %cd%
																																						SetLocal EnableExtensions EnableDelayedExpansion
																																						set fsz = 4190109696
																																						set sfo = % 1\PARAM.SFO
																																						set fdr = % 1
																																						set fdr = !fdr:"=!
																																						for %%I in(!fdr!) do (set nm = %%~nxI)
																																							for %%I in(!fdr!) do (set fp = %%~fxI)
																																								set fnm = !fp : %nm %= !
																																								set dnm = !nm!
																																								for / f "usebackq" %%n in(`!src!\sfk strlen !fnm!`) do set len = %%n
																																									set / a len = !len!- 1
																																									set fnn = !fnm:~0, %len % !
																																									cd !fnm!
																																									set tp = %cd%\temp
																																									if exist !tp!rd / s / q !tp!
																																										md !tp!
																																										copy !src!\dirsplit.exe !fnm!> nul
																																										dirsplit.exe !dnm!!fsz!

																																										set chk = chunk - *.txt
																																										set big = big - *.txt

																																										if not exist !sfo!(
																																											echo Not find !sfo!
																																											echo Exiting...
																																											goto exit
																																											)
																																											if exist "%big%" (
																																												type %big%
																																												echo.
																																												echo Examine these files, if files archive, then perhaps you can unpack and then divide
																																												echo The game has a file of more than %fsz% byte.This folder can not be divided into parts.
																																												echo Exiting...
																																												echo.
																																												goto exit
																																												)

																																												rem::Получаем ContentID из EBOOT.BIN, если присутствует
																																												if exist "!fdr!\USRDIR\EBOOT.BIN" (
																																													"!src!\sfk" hexdump - pure - nofile - rawname - offlen 0x450 0x24 "!fdr!\USRDIR\EBOOT.BIN" + hextobin "!tp!\cid.txt" > nul
																																													for / f "usebackq" %%I in("!tp!\cid.txt") do set cid = %%I
																																														set cidend = !cid:~20, 14!
																																														echo !fdr!\USRDIR\EBOOT.BIN
																																														)

																																													rem Получаем ContentID из ISO.BIN.EDAT, если присутствует
																																														if exist "!fdr!\USRDIR\ISO.BIN.EDAT" (
																																															"!src!\sfk" hexdump - pure - nofile - rawname - offlen 0x10 0x24 "!fdr!\USRDIR\ISO.BIN.EDAT" + hextobin "!tp!\cid.txt" > nul
																																															for / f "usebackq" %%I in("!tp!\cid.txt") do set cid = %%I
																																																set cidend = !cid:~20, 14!
																																																)
																																															rem Бэкапим PARAM.SFO, ICON0.PNG и EBOOT.BIN во временную папку
																																																if exist "!sfo!" xcopy / y "!sfo!" "!tp!" > nul
																																																	if exist "!fdr!\ICON0.PNG" xcopy / y "!fdr!\ICON0.PNG" "!tp!" > nul
																																																		if exist "!fdr!\USRDIR\EBOOT.BIN" xcopy / y "!fdr!\USRDIR\EBOOT.BIN" "!tp!" > nul

																																																			rem Получаем имя чанка и его номер в порядке деления по 4 ГБ
																																																			for %%A in("!chk!") do (
																																																				set fn = %%~nA
																																																				set ch = !fn:~6, 2!
																																																				rem Копируем файлы по списку из каждого чанка в свою папку с названием текущего чанка
																																																				echo Preparing folder for the parts : !fn!
																																																				echo.
																																																				echo Moving the !fn!files to the SPLITTED folder.Please wait...

																																																				for / f "usebackq tokens=* delims=" %%B in("%%A") do (
																																																					attrib - r "!fnm!%%~B"
																																																					set pn = %%B
																																																					xcopy "!fnm!%%~B" "!fnm!SPLITTED\!fn!\!pn:%%~nxB=!" / t / e > nul
																																																					move "!fnm!%%~B" "!fnm!SPLITTED\!fn!\!pn:%%~nxB=!" > nul
																																																					)

																																																					if exist "!tp!\PARAM.SFO" xcopy / y "!tp!\PARAM.SFO" "!fnm!SPLITTED\!fn!\!dnm!" > nul
																																																						if exist "!tp!\ICON0.PNG" xcopy / y "!tp!\ICON0.PNG" "!fnm!SPLITTED\!fn!\!dnm!" > nul
																																																							if exist "!tp!\EBOOT.BIN" xcopy / y "!tp!\EBOOT.BIN" "!fnm!SPLITTED\!fn!\!dnm!\USRDIR" > nul
																																																								rem Проверяем наличие пустых папок и заполняем их фейковым текстовым файлом
																																																								for / f "tokens=* delims=" %%C in('dir /ad /b /s "!fnm!SPLITTED\!fn!\!dnm!\USRDIR\"') do dir / b "%%C" | > nul find / v "" || echo PSPx Team © > "%%C\!dnm!.txt"

																																																									rem Приступаем к подготовке данных для конфига
																																																									set conf = "!tp!\package.conf"
																																																									for / f "usebackq tokens=3" %%D in(`!src!\sfoprint "!tp!\PARAM.SFO" TITLE_ID`) do set title = %%D00000!ch!
																																																										for / f "usebackq tokens=3" %%E in(`!src!\sfoprint "!tp!\PARAM.SFO" CATEGORY`) do set cat = %%E
																																																											for / f "usebackq tokens=3" %%F in(`!src!\sfoprint "!tp!\PARAM.SFO" APP_VER`) do set apver = %%F
																																																												if not defined apver set apver = 1.00
																																																													set DRM = Free
																																																													if !cat != = HD(
																																																														set ct = Game_Exec
																																																														set pt = HDDGamePatch
																																																														set n1 = 1HDCAT
																																																													)
																																																														if !cat != = HG(
																																																															set ct = Game_Exec
																																																															set pt = HDDGamePatch
																																																															set n1 = 1HGCAT
																																																														)
																																																															if !cat != = DG(
																																																																set ct = Game_Exec
																																																																set pt = HDDGamePatch
																																																																set n1 = 1DGCAT
																																																															)
																																																																if !cat != = GD(
																																																																	set ct = Game_Data
																																																																	set pt = DiscGamePatch
																																																																	set n1 = 2PATCH
																																																																)
																																																																	if !cat != = AP(
																																																																		set ct = Game_Exec
																																																																		set pt = HDDGamePatch
																																																																		set n1 = 1APCAT
																																																																		set title = APPPHOTO000000!ch!
																																																																	)
																																																																		if !cat != = AM(
																																																																			set ct = Game_Exec
																																																																			set pt = HDDGamePatch
																																																																			set n1 = 1AMCAT
																																																																			set title = APPMUSIC000000!ch!
																																																																		)
																																																																			if !cat != = AV(
																																																																				set ct = Game_Exec
																																																																				set pt = HDDGamePatch
																																																																				set n1 = 1AVCAT
																																																																				set title = APPVIDEO000000!ch!
																																																																			)
																																																																				if !cat != = AT(
																																																																					set ct = Game_Exec
																																																																					set pt = HDDGamePatch
																																																																					set n1 = 1ATCAT
																																																																					set title = APPTV000000000!ch!
																																																																				)
																																																																					if !cat != = 2G(
																																																																						set EDT = ISO.BIN.EDAT
																																																																						set ct = Game_Data
																																																																						set n1 = 12GCAT
																																																																						set title = PS2DISCINSTALL!ch!
																																																																					)
																																																																						if !cat != = 2P(
																																																																							set EDT = ISO.BIN.EDAT
																																																																							set ct = Game_Data
																																																																							set n1 = 12PCAT
																																																																							set title = PS2CLASSICS000!ch!
																																																																						)
																																																																							if !cat != = 2D(
																																																																								set EDT = ISO.BIN.EDAT
																																																																								set ct = Game_Data
																																																																								set n1 = 22DCAT
																																																																								set title = PS2EMUDATA0000!ch!
																																																																							)
																																																																								if !cat != = 1P(
																																																																									set EDT = ISO.BIN.EDAT
																																																																									set ct = Game_Data
																																																																									set n1 = 11PCAT
																																																																									set title = PS1CLASSICS000!ch!
																																																																								)
																																																																									if !cat != = MN(
																																																																										set EDT = ISO.BIN.EDAT
																																																																										set ct = minis
																																																																										set n1 = 1MNCAT
																																																																										set title = PSPMINIS000000!ch!
																																																																									)
																																																																										if !cat != = PE(
																																																																											set EDT = ISO.BIN.EDAT
																																																																											set ct = Game_Data
																																																																											set n1 = 1PECAT
																																																																											set title = PSPREMASTERS00!ch!
																																																																										)
																																																																											if !cat != = PP(
																																																																												set EDT = ISO.BIN.EDAT
																																																																												set ct = Game_Data
																																																																												set n1 = 1PPCAT
																																																																												set title = PSPGAME0000000!ch!
																																																																											)
																																																																												echo.
																																																																												echo Making DEBUG PKG...
																																																																												"!src!\sfoprint" "!tp!\PARAM.SFO" TITLE
																																																																												if defined cid echo ContentID : !cid!
																																																																													"!src!\sfoprint" "!tp!\PARAM.SFO" TITLE_ID
																																																																													echo GAME_DIR : !dnm!: !fn!
																																																																													if defined cid set title = !cidend!!ch!
																																																																														rem Создаём конфиг
																																																																														echo Content - ID = !n1!- !dnm : ~0, 9!_00 - !title!> !conf!
																																																																														echo k_licensee = 0x00000000000000000000000000000000 >> !conf!
																																																																														echo DRM_Type = !DRM!>> !conf!
																																																																														echo Content_Type = !ct!>> !conf!
																																																																														if defined pt echo PackageType = !pt!>> !conf!
																																																																															echo InstallDirectory = !dnm!>> !conf!
																																																																															echo PackageVersion = !apver!>> !conf!
																																																																															rem Конвертируем Debug PKG
																																																																															"!src!\psn_package_npdrm" - n - f !conf!"!fnm!SPLITTED\!fn!\!dnm!"

																																																																															echo Move !fn!files from the SPLITTED folder back to the original folder.Please wait...
																																																																															for / f "usebackq tokens=* delims=" %%B in("%%A") do (
																																																																																set pn = %%B
																																																																																move "!fnm!SPLITTED\!fn!\%%~B" "!fnm!!pn:%%~nxB=!" > nul
																																																																																)
																																																																																del / q "!fnm!!fn!.txt" && rd / s / q "!fnm!SPLITTED"
																																																																																echo.
																																																																																if exist "!fnm!\!n1!-!dnm:~0,9!_00-!title!.pkg" (
																																																																																	set / a deb += 1

																																																																																	echo DONE^^!!deb!Debug PKG created : "!n1!-!dnm:~0,9!_00-!title!.pkg"
																																																																																	set debug = !deb!Debug PKG : !n1!- !dnm : ~0, 9!_00 - !title!.pkg
																																																																																	echo.
																																																																																	if !EDT != = ISO.BIN.EDAT(
																																																																																		echo Signing DEBUG PKG to RETAIL...
																																																																																		"!src!\sfoprint" "!tp!\PARAM.SFO" TITLE
																																																																																		if defined cid echo ContentID : !cid!
																																																																																			"!src!\sfoprint" "!tp!\PARAM.SFO" TITLE_ID
																																																																																			echo.
																																																																																			echo | "!src!\ps3xploit_rifgen_edatresign" "!fnm!\!n1!-!dnm:~0,9!_00-!title!.pkg"
																																																																																			echo.
																																																																																			del "!fnm!\!n1!-!dnm:~0,9!_00-!title!.pkg" / q
																																																																																			rem Если юзер оставил PKG от предыдущих компиляций, переносим в папку BACKUP
																																																																																			if exist "!fnm!\!n1!-!dnm:~0,9!_00-!title!_signed.pkg" (
																																																																																				echo Found file from previous compilation : "!n1!-!dnm:~0,9!_00-!title!_signed.pkg"
																																																																																				echo The old file will be moved to the "BACKUP" folder.
																																																																																				if not exist "!fnm!\BACKUP" md "!fnm!\BACKUP"
																																																																																					move / y "!fnm!\!n1!-!dnm:~0,9!_00-!title!_signed.pkg" "!fnm!\BACKUP"
																																																																																					)
																																																																																				ren "!fnm!\!n1!-!dnm:~0,9!_00-!title!.pkg_signed.pkg" "!n1!-!dnm:~0,9!_00-!title!_signed.pkg"
																																																																																					echo.
																																																																																					set / a sig += 1
																																																																																					title !sig!Signed Retail PKG created
																																																																																					echo DONE^^!!sig!Signed Retail PKG created : "!n1!-!dnm:~0,9!_00-!title!_signed.pkg"
																																																																																					set signed = !sig!Signed PKG : !n1!- !dnm : ~0, 9!_00 - !title!_signed.pkg
																																																																																					echo.
																																																																																					)
																																																																																		)
																																																																																	)
																																																												if not !EDT != = ISO.BIN.EDAT echo All Done. %deb% DEBUG PKG for PS3 is converted. %debug%.You can install the game from 'HAN Debug PKG Enabler'
																																																													if !EDT != = ISO.BIN.EDAT echo All Done. %sig% Signed Retail PKG for PS3 is converted. %signed%.You can install the game from 'HAN Enabler' mode.
																																																														del / q !fnm!dirsplit.exe %chk%
																																																														if exist !tp!rd / s / q !tp!
																																																															:exit
																																																															start "" "!fnm!"
																																																															if defined cons pause
																											}