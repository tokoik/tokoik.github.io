#!/usr/bin/perl

# EZBBS ver2.00(02/05/23)
# ver1.00(01/04/17)
# Copyright(c) Aya
# aya@magic.104.net
# http://www.ayavv.net/d/index.htm

# バージョン情報
$ver = 'EZBBS v2.00';

# ++ NOTICE ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# ◇このスクリプトは、フリーソフトです。このスクリプトを使用したいかなる
# 　損害に対しても、作者はその一切の責を負いません。
# ◇設置に関する質問はサポート掲示板にお願いします。メールを送って
# 　いただいてもお返事はいたしません。
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# ========
# 設定項目
# ========

require './jcode.pl';				# 文字コードライブラリ取込

$title = "メディアデザイン演習 意見交換 BBS";	# タイトル名を指定
$title_gif = '';				# タイトル画像(使用しないときは''）
$tg_w = '320';					# タイトル画像の幅
$tg_h = '80';					# タイトル画像の高さ
$home_url = '../index.html';			# 戻り先のURL (index.htmlなど)
$target = '_self';				# 戻り先のターゲット指定
$twid = '80%';					# 表示幅（%値かピクセル値で）
$tpost = 'center';				# 配置場所(left/center/right)

$pass = 'mediadesign';				# 管理用パスワード
$my_clr = 0;					# 管理人専用文字色機能(0=no/1=yes)
$m_clr = '';					# 管理人用文字色

$sub_len = '15';				# 記事タイトルの文字数制限(全角換算)
$max = 50;					# 最大記事数
$p_log = 10;					# 1ページあたりの親記事表示数
$autolink = 1;					# URLの自動リンク(0=no/1=yes)

$style = './style.css';				# スタイルシートの場所
$inputbtn = 'inputbtn';				# ボタンの色(IEのみ適用)
$inputfrm = 'inputfrm';				# テキストフォーム
$fbgclr = 'fbgclr';				# フォーム部分他の枠色
$tbgclr = 'tbgclr';				# フォーム部分他地色

$script = "./ezbbs.cgi";			# スクリプトの場所
$logfile = './ezbbs.log';			# ログファイルの場所
$method = 'POST';				# methodの形式 (POST/GET)
$lockkey = 0;					# ファイルロック形式(0=no/1=open関数)
$lockfile = './ezbbs.lock';			# ロックファイル名
$fontcolor = './fontcolor.dat';			# フォントカラーの場所
$get_host = 0;					# ホスト名取得モード(0:$ENV{'REMOTE_HOST'}/1:gethostbyaddr)

@DENY = (					# アクセス拒否
	"*.host.ne.jp",
	"210.150.200.*",
	""
	);

# ==================================
# 設定ここまで。この先はいじらないこと
# ==================================

# ----- メイン処理 -----
&decode;
&deny_host;
if ($FORM {'mode'} eq "regist"){&regist;}
elsif($FORM{'mode'} eq "color"){&color;}
elsif ($FORM {'mode'} eq "delete"){&delete;}
elsif ($FORM {'mode'} eq "admin"){&admin;}
&print_html;

# ----- ブラウザに表示 -----
sub print_html {
	&get_cookie;
	&get_agent;
	&header;

	if($title_gif ne ''){
		print qq#<center>\n<img src="$title_gif" width="$tg_w" height="$tg_h">#;
		print qq#<br>\n<br>\n</center>#;
	}

	print qq#<div align="$tpost">\n<table><tr><td class="$fbgclr"><table cellpadding="5" cellspacing="1">\n#;
	print qq#<tr>\n<td colspan="3" align="center" class="$tbgclr">\n#;

	if ($title_gif eq ''){print "<br>\n<H1>$title</H1>\n";}

	&form;

	print << "EOD";
<p align="left">・この掲示板はクッキー対応です。<br>
・投稿内容にタグは一切使用できません。<br>
・文字化けの原因となるので半角カナは使用しないでください。<br>
・削除キーで記事を削除できますが、親記事を削除するとレス記事も削除されます。</p>
<div align="right"><small>$ver / <a href="http://www.ayavv.net/d/index.htm" target="_blank">D-cyst</a></small></div>
</td>
</tr>
<tr>
<td align="center" class="$tbgclr" nowrap>
<a href="$home_url" target="$target">ホームページ</a>
</td>
<td align="center" class="$tbgclr" nowrap>
<form action="$script" method="$method">
<input type="hidden" name="mode" value="delete">
<b>NO</b><input type="text" name="no" size="4" class="$inputfrm">
 <b>削除キー</b><input type="password" name="pwd" size="6" class="$inputfrm">
 <input type="submit" value="記事削除" class="$inputbtn">
</form>
</td>
<td align="center" class="$tbgclr" nowrap>
<form action="$script" method="$method">
<input type="hidden" name="mode" value="admin">
<input type="password" name="pass" size="8" class="$inputfrm">
<input type="submit" value="管理者用" class="$inputbtn">
</form>
</td>
</tr>
</table>
</td>
</tr>
</table>
</div>
<br>
<br>
EOD

	open(IN,"$logfile") || &error("Open Error : logfile");
	@lines= <IN>;
	close(IN);

	$numb = shift(@lines);

	@new = ();
	foreach $line(@lines){
		local($num,$date,$name,$email,$sub,$com,$url,$host,$fntclr,$pw,$resnum) = split(/<>/,$line);
		if($resnum eq ""){push(@new,$line);}
	}

	$i = 0; $j = 0;
	foreach $line(@new){
		($num,$date,$name,$email,$sub,$com,$url,$host,$fntclr) = split(/<>/,$line);
		
		$i++;
		if($page eq ""){
			if($i >$p_log){last;}
		} else {
			if($i < $page){next;}
			else{
				$j++;
				if($j > $p_log){last;}
			}
		}

		if ($email){ $email = " * <a href=\"mailto\:$email\">MAIL</a> "; }
		if ($url){ $url = " * <a href=\"http://$url\" target=\"_blank\">HOME</a>\n"; }

		print qq#<DIV align="$tpost">\n<table width="$twid">\n<tr>\n#;
		print qq#<td bgcolor="$fntclr" align="center">\n#;
		print qq#<table width="100%" cellspacing="0">\n<tr>\n<td class="$tbgclr">\n#;
		print qq#<table width="100%" cellpadding="5">\n<tr>\n#;
		print qq#<td>\n<b><font color="$fntclr">* $sub *</font></b> <b>$name</b>$email$url</td>\n</tr>\n#;
		print qq#<tr>\n<td>\n<blockquote>\n<font color="$fntclr">$com<br>\n#;
		print qq#<small>[ $date - $fntclr - no.$num ] </small></font>\n</blockquote>\n#;

		$flag = 0;
		foreach $line(@lines){
			($rnum,$rd,$rna,$rem,$rsub,$rcom,$rurl,$rho,$rclr,$rpw,$rr) = split(/<>/,$line);
			if($num eq "$rr"){
				if($flag == 0){
					print qq#<div align="right">\n<table width="90%">\n#;
					print qq#<tr>\n<td>\n<hr size=1>\n#;
					$flag = 1;
				}
				else{
					print qq#<div align="right">\n<table width="90%">\n#;
					print qq#<tr>\n<td>\n#;
				}
				print qq#<font color="$rclr"><b>$rna</b> ＞ $rcom\n#;
				print "　<small>[ $rd - no.$rnum ]</small><br>\n";
				print "</td>\n</tr>\n</table>\n</div>\n";
			}
		}

		print qq#</td>\n</tr>\n<tr>\n<td align="center" nowrap><hr>\n#;

		&resform;

		print "</tr>\n</table>\n</td>\n</tr>\n</table>\n";
		print "</td>\n</tr>\n</table>\n</div>\n<br>\n<br>\n";

	}

	if($page eq ''){$page =1;}
	$next_line = $page + $p_log;
	$back_line = $page - $p_log;

	print qq#<div align="$tpost">\n<table width="$twid">\n<tr>\n#;
	print qq#<td align="center">\n<table>\n<tr>\n#;

	if($back_line >0){
		print qq#<td><form method="$method" action="$script">\n#;
		print qq#<input type="hidden" name="page" value="$back_line">\n#;
		print qq#<input type="submit" value="前の$p_log件" class="$inputbtn">\n#;
		print "</form>\n</td>\n";
	}
	if($next_line <= $i){
		print qq#<td><form method="$method" action="$script">\n#;
		print qq#<input type="hidden" name="page" value="$next_line">\n#;
		print qq#<input type="submit" value="次の$p_log件" class="$inputbtn">\n#;
		print "</form>\n</td>\n";
	}
	print "</tr>\n</table>\n</td>\n</tr>\n</table>\n</div>\n";

	&footer;
	exit;
}

# ----- 投稿フォーム -----
sub form{
	print << "EOD";
<form method="$method" action="$script">
<input type="hidden" name="mode" value="regist">
<table>
<tr>
<td nowrap align="right"><b>なまえ</b>
</td>
<td colspan="2"><input type="text" name="name" size="$nam_wid" value="$c_name" class="$inputfrm">
</td>
</tr>
<tr>
<td nowrap align="right"><b>Eメール</b>
</td>
<td colspan="2"><input type="text" name="email" size="$sub_wid" value="$c_email" class="$inputfrm">
</td>
</tr>
<tr>
<td nowrap align="right"><b>タイトル</b>
</td>
<td colspan="2">
<input type="text" name="sub" size="$sub_wid" class="$inputfrm">
</td>
</tr>
<tr>
<td nowrap align="right"><b>URL</b>
</td>
<td colspan="2"><input type="text" name="url" size="$url_wid" value="http://$c_url" class="$inputfrm">
</td>
</tr>
<tr>
<td nowrap colspan="3"><b>メッセージ</b><br>
<textarea cols="$com_wid" rows="8" name="comment" wrap="soft"></textarea>
</td>
</tr>
<tr>
<td nowrap align="right"><b>文字色</b>
</td>
<td colspan="2"><select name="fntclr">
EOD

	if ($c_fntclr){print "<option selected>$c_fntclr\n";}

	open(FONT,"$fontcolor") || die"Open Error : fontfile";@fonts=<FONT>;

	if($my_clr){push(@fonts,"$m_clr ");}

	foreach(@fonts){chop;print "<option>$_\n";}
	close(FONT);

	print <<"EOD";
</select>
 * <a href="$script?mode=color" target="_blank">カラーサンプル</a> *
 <small>別ウィンドウで開きます</small>
</td>
</tr>
<tr>
<td nowrap align="right"><b>削除キー</b>
</td>
<td><input type="password" name="pwd" size="8" maxlength="8" value="$c_pwd" class="$inputfrm">
 <small>記事削除に使用。英数字で8文字以内</small>
</td>
<td align="right"><input type="submit" value="投稿する" class="$inputbtn">
</td>
</tr>
</table>
</form>
EOD
}

# ----- 返信フォーム -----
sub resform{
	print << "EOD";
<form method="$method" action="$script">
<input type=hidden name=mode value="regist">
<input type=hidden name=resnum value="$num">
<input type=hidden name=page value="$page">
<input type=hidden name=email value="$c_email">
<input type=hidden name=url value="$c_url">
<input type=hidden name=fntclr value="$c_fntclr">
<input type=hidden name=pwd value="$c_pwd">
<b>なまえ</b> <input type=text name=name size="10" value="$c_name" class="$inputfrm">
<b>文字色</b>
 <select name=fntclr>
EOD

	if($c_fntclr){print "<option selected>$c_fntclr\n";}

	open(FONT,"$fontcolor") || die"Open Error : fontfile";@fonts=<FONT>;

	if($my_clr){push(@fonts,"$m_clr ");}

	foreach(@fonts){chop;print "<option>$_\n";}
	close(FONT);

	print << "EOD";
</select>
 <b>削除キー</b>
 <input type="password" name="pwd" size="5" maxlength="8" value="$c_pwd" class="$inputfrm">
<br>
<b>メッセージ</b>
<br>
<textarea cols="$url_wid" rows="4" name="comment" wrap="soft"></textarea>
 <input type=submit value="投稿する" class="$inputbtn">
</form>
EOD
}

# ----- デコードルーチン -----
sub decode{
	if ($ENV{'REQUEST_METHOD'} eq "POST") {
		read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});
	} else { $buffer = $ENV{'QUERY_STRING'}; }

	@pairs = split(/&/, $buffer);
	foreach $pair (@pairs) {
		($name,$value) = split(/=/, $pair);
		$value =~ tr/+/ /;
		$value =~ s/%([a-fA-F0-9][a-fA-F0-9])/pack("C", hex($1))/eg;

		&jcode'convert(*value,'euc');

		$value =~ s/</&lt;/g;
		$value =~ s/>/&gt;/g;

		if ($name eq "del") { push(@DEL,$value); }

		$FORM{$name} = $value;
	}
	$page = $FORM{'page'};
}

# ----- 書き込み処理 -----
sub regist{
	if ($FORM{'name'} eq ""){ &error("名前を書いてください");}
	if ($FORM{'comment'} eq "") { &error("メッセージを書いてください");}
	if(length($FORM{'sub'}) > $sub_len*2){ &error(" 題名の長さは全角$sub_len文字までにして下さい");}
	if($my_clr && $FORM{'fntclr'} eq "$m_clr"){
		if($FORM{'pwd'} ne "$pass"){ &error("$m_clrは管理者専用の色です");}
	}

	$FORM{'comment'} =~ s/\r\n/<br>/g;
	$FORM{'comment'} =~ s/\r/<br>/g;
	$FORM{'comment'} =~ s/\n/<br>/g;
	$FORM{'url'} =~ s/^http\:\/\///;
	if($FORM{'sub'} eq "") {
		if($lang){$FORM{'sub'} = "無題";}
		else{$FORM{'sub'} = "no title";}
	}

	&get_time;
	&get_host;
	&set_cookie;
	if($lockkey == 1){&lock;}

	open(IN,"$logfile") || &error("Open Error : logfile");
	@lines = <IN>;
	close(IN);

	$numb = shift(@lines);
	$numb =~ s/\n//;
	$numb++;

	foreach $line(@lines){
		($bnum,$bdate,$bname,$bemail,$bsub,$bcom,$burl,$bhost,$bfntclr,$pw,$resn) = split(/<>/,$line);
		if($FORM{'name'} eq "$bname" && $FORM{'comment'} eq "$bcom") { &error("二重投稿です");}
	}

	if($FORM{'pwd'}){$PW = &make_pwd($FORM{'pwd'});}
	if($autolink){&auto_link($FORM{'comment'});}

	if($FORM{'resnum'} eq ""){
		@new = ();
		$i = 0;
		$stop = 0;
		foreach $line(@lines){
			($num,$d,$na,$em,$sub,$com,$url,$ho,$clr,$p,$r) = split(/<>/,$line);
			if($r eq ""){$i++;}
			if($i > $max-1){
				$stop = 1;
				last;
			}
			if($stop == 0){push(@new,$line);}
		}
		unshift(@new,"$numb<>$date<>$FORM{'name'}<>$FORM{'email'}<>$FORM{'sub'}<>$FORM{'comment'}<>$FORM{'url'}<>$host<>$FORM{'fntclr'}<>$PW<>$FORM{'resnum'}<>\n");
		unshift(@new,"$numb\n");
		open(OUT,">$logfile") || &error("Write Error : logfile");
		print OUT @new;
		close(OUT);
	}
	elsif($FORM{'resnum'} ne ""){
		@res_msg = ();
		@new = ();
		foreach $line(@lines){
			$flag = 0;
			($num,$d,$na,$em,$sub,$com,$u,$ho,$clr,$p,$r) = split(/<>/,$line);
			if($r eq "" && $FORM{'resnum'} eq "$num"){
				$new_line = "$line";
				$flag = 1;
			}
			elsif($r eq "$FORM{'resnum'}"){
				push(@res_msg,$line);
				$flag = 1;
			}
			if($flag == 0){push(@new,$line);}
		}
		unshift(@new,"$numb<>$date<>$FORM{'name'}<>$FORM{'email'}<>$FORM{'sub'}<>$FORM{'comment'}<>$FORM{'url'}<>$host<>$FORM{'fntclr'}<>$PW<>$FORM{'resnum'}<>\n");
		unshift(@new,"@res_msg");
		unshift(@new,"$new_line");
		unshift(@new,"$numb\n");
		open(OUT,">$logfile") || &error("Write Error : logfile");
		print OUT @new;
		close(OUT);
	}
	if($lockkey == 1){&unlock;}
}

# -----ファイルロック -----
sub lock{
	local ($flag) = 0;
	foreach(1 .. 5){
		if (-e $lockfile) { sleep(1);}
		else {
			 open ( LOCK,">$lockfile");
			close(LOCK);
			$flag =1;
			last;
		}
	}
	if ($flag == 0) { &error ("Lock Error");}
}

sub unlock{
	if (-e $lockfile) { unlock($lockfile);}
}

# ----- エラー処理 -----
sub error{
	if($lockkey == 1){&unlock;}
	&header;

	print << "EOD";
<center>
<table width="400">
<tr>
<td align="center" class="$fbgclr">
<table width="100%" cellspacing="0">
<tr>
<td align="center" class="$tbgclr"><br><H1>error</H1>
<p><b>$_[0]</b></p><br>
</td>
</tr>
</table>
</td>
</tr>
</table>
</center>
</body>
</html>
EOD
	exit;
}

# ----- HTMLヘッダー -----
sub header{
	print << "EOD";
Content-type:text/html

<html>
<head>
<meta HTTP-EQUIV="Content-type" CONTENT="text/html; charset=EUC-JP">
<link rel="stylesheet" href="$style">
<title>$title</title>
</head>
<body>
EOD
}

# ----- HTMLフッター -----
sub footer{
	print "</body>\n</html>";
}

# ----- URL自動リンク -----
sub auto_link {
	$_[0] =~ s/([^=^\"]|^)(http\:[\w\.\~\-\/\?\&\+\=\:\@\%\;\#\%]+)/$1<a href=\"$2\" target='_blank'>CLICK!<\/a>/g;
}

# ----- カラーサンプル -----
sub color{
	&header;
	&get_agent;

	print << "EOD";
<div align="$tpost">
<table width="400">
<tr>
<td align="center" class="$fbgclr">
<table width="100%" cellspacing="0">
<tr>
<td class="$tbgclr" align="center">
<a name=top></a><br>
この掲示板で使用できる色の一覧です。<br>
｢文字色｣で指定してください。
<hr width="90%">
EOD

	open(FONT,"$fontcolor") || &error("Open Error : fontfile");
	while($_ = <FONT>){
		chop;
		print "<font color=$_><b>$_</b> はこのような色になります</font><br>\n<br>\n";
		}
	close(FONT);

	print << "EOD";
<hr width="90%">
<INPUT type="button" value="ウィンドウを閉じる" onclick="window.close()" class="$inputbtn"><br>
<br>
</td>
</tr>
</table>
</td>
</tr>
</table>
</div>
EOD

	&footer;
	exit;
}

# ----- 投稿者記事削除 -----
sub delete{
	if($FORM{'no'} eq ""){ &error("記事NOが入力されていません");}
	if($FORM{'pwd'} eq ""){ &error("パスワードが入力されていません");}

	if($lockkey == 1){&lock;}

	open(IN,"$logfile") || &error("Open Error : logfile");
	@lines = <IN>;
	close(IN);

	$numb = shift(@lines);

	local($flag) = 0;
	@new = ();
	foreach (@lines){
		($num,$date,$name,$email,$sub,$com,$url,$host,$fntclr,$pw,$resnum) = split(/<>/,$_);
		if($flag == 0 && $FORM{'no'} eq "$num"){
			$PW = $pw;
			if($resnum eq ""){$flag = 2;}
			else{$flag=1;}
		}
		elsif($flag == 2 && $FORM{'no'} eq "$resnum"){next;}
		else{push(@new,$_);}
	}

	if ($flag == 0){&error("該当記事が見あたりません");}
	if ($PW eq ""){&error("削除キーが設定されていません");}

	$result = &match_pwd("$FORM{'pwd'}","$PW");
	if($result ne 'OK'){&error("削除キーが違います");}

	unshift(@new,$numb);

	open(OUT,">$logfile") || &error("Write Error : logfile");
	print OUT @new;
	close(OUT);

	if($lockkey == 1){&unlock;}
}

# ----- 管理モード -----
sub admin{
	if($FORM{'pass'} ne "$pass") { &error("Wrong Password");}

	if($lockkey == 1){&lock;}

	open(IN,"$logfile") || &error ("Open Error : logfile");
	@lines = <IN>;
	close(IN);

	$numb = shift(@lines);

	if ($DEL[0]){
		@new=();
		foreach (@lines) {
			$flag=0;
			($num,$date,$name,$email,$sub,$com,$url,$host,$fntclr,$pw,$resnum) = split(/<>/,$_);
			foreach $x (@DEL){
				if ($num eq "$x" || $resnum eq "$x") {
					$flag=1; last;
				}
			}
			if ($flag == 0) { push(@new,$_);
		}
	}

	unshift(@new,"$numb");
	open(OUT,">$logfile") || &error ("Write Error : logfile");
	print OUT @new;
	close(OUT);

	@lines=@new;
	$numb = shift(@lines);
	}

	if($lockkey == 1){&unlock;}

	&header;

	print << "EOD";
<div align="$tpost">
<table width="80%">
<tr>
<td align="center" class="$fbgclr">
<table width="100%" cellspacing="0" cellpadding="5">
<tr>
<td align="center" class="$tbgclr"><br>
<div align="left">[ <a href="$script?">もどる</a> ]</div>
<p align="left">・削除したい記事NOにチェックを入れ｢削除する｣ボタンを押してください。<br>
・タイトルの付いている記事は親記事です。タイトル部が｢*｣となっているのがレス記事です。<br>
・親記事を削除すると関連レス記事も同時に削除されます。</p>
<form method="$method" action="$script">
<input type="hidden" name="mode" value="admin">
<input type="hidden" name="pass" value="$FORM{'pass'}">
<input type="submit" value="削除する" class="$inputbtn">
<input type="reset" value="リセット" class="$inputbtn"><br>
<br>
<table width="95%" border="1" cellspacing="0" cellpadding="3">
<tr>
<th nowrap>NO</th>
<th nowrap>TITLE</th>
<th nowrap>NAME</th>
<th nowrap>MESSAGE</th>
<th nowrap>DATE</th>
<th nowrap>HOST</th>
</tr>
EOD

	if($page eq ""){$page = 0;}
	$start = $page + 1;
	$end   = $page + $p_log;

	$i = 0; $j = 0;
	foreach(@lines) {
		($num,$date,$name,$email,$sub,$com,$url,$host,$fntclr,$pw,$resnum) = split(/<>/,$_);
		if ($email){$name = "<a href=\"mailto:$email\">$name</a>";}

		if ($resnum eq "") { $i++; $j++; }
		if ($i < $start) { next; }
		if ($i > $end) { next; }

		$com =~ s/<br>//g;
		if (length($com) > 50) {
			$com = substr($com,0,48);
			$com .= '..';
		}

		if($resnum eq ""){
			print qq#<tr>\n<td><input type="checkbox" name="del" value="$num">#;
			print "<b>$num</b></td>\n<th>$sub</th>\n";
			print qq#<td align="center">$name</td>\n<td><small>$com</small></td>\n#;
			print "<td><small>$date</small></td>\n<td><small>$host</small></td>\n</tr>\n";
		}else{
			print qq#<tr>\n<td><input type="checkbox" name="del" value="$num">#;
			print qq#<b>$num</b></td>\n<td align="center">*</td>\n#;
			print qq#<td align="center">$name</td>\n<td><small>$com</small></td>\n#;
			print "<td><small>$date</small></td>\n<td><small>$host</small></td>\n</tr>\n";
		}
	}

	print "</table>\n</p>\n</form>\n";

	$next_line = $page + $p_log;
	$back_line = $page - $p_log;

	print qq#<div align="$tpost">\n<table width="$twid">\n<tr>\n#;
	print qq#<td align="center">\n<table>\n<tr>\n#;

	if($back_line >= 0){
		print qq#<td><form method="$method" action="$script">\n#;
		print qq#<input type="hidden" name="mode" value="admin">\n#;
		print qq#<input type="hidden" name="pass" value="$FORM{'pass'}">\n#;
		print qq#<input type="hidden" name="page" value="$back_line">\n#;
		print qq#<input type="submit" value="前の$p_log件" class="$inputbtn">\n#;
		print "</form>\n</td>\n";
	}
	if($next_line < $i){
		print qq#<td><form method="$method" action="$script">\n#;
		print qq#<input type="hidden" name="page" value="$next_line">\n#;
		print qq#<input type="hidden" name="mode" value="admin">\n#;
		print qq#<input type="hidden" name="pass" value="$FORM{'pass'}">\n#;
		print qq#<input type="submit" value="次の$p_log件" class="$inputbtn">\n#;
		print "</form>\n</td>\n";
	}
	print "</tr>\n</table>\n</td>\n</tr>\n</table>\n</div>\n";

	print "</td>\n</tr>\n</table>\n</td>\n</tr>\n</table>\n</center>\n";

	&footer;
	exit;
}

# ----- ホスト名取得 -----
sub get_host{
	$host = $ENV{'REMOTE_HOST'};
	$addr = $ENV{'REMOTE_ADDR'};
	if($get_host){
		if($host eq "" || $host eq "$addr"){
			$host = gethostyaddr(pack("C4",split(/\./,$addr)),2);
		}
	}
	if($host eq ""){$host = $addr;}
}

# ----- クッキー発行 -----
sub set_cookie{
	($secg,$ming,$hourg,$mdayg,$mong,$yearg,$wdayg,$ydayg,$isdstg) = gmtime(time + 60*24*60*60);

	$yearg += 1900;
	if($secg < 10){$secg = "0$secg";}
	if($ming < 10){$ming = "0$ming";}
	if($hourg < 10){$hourg = "0$hourg";}
	if($mdayg < 10){$mdayg = "0$mdayg";}

	$month = ('Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec')[$mong];
	$week = ('Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday')[$wdayg];
	$date_gmt = "$week,$mdayg\-$month\-$yearg $hourg:$ming:$secg GMT";

	$cook = "name\:$FORM{'name'}\,email\:$FORM{'email'}\,url\:$FORM{'url'}\,fntclr\:$FORM{'fntclr'}\,pwd\:$FORM{'pwd'}";
	print "Set-Cookie: EZBBS=$cook; expires=$date_gmt\n";
}

# ----- クッキー取得 -----
sub get_cookie{
	@pairs = split(/;/,$ENV{'HTTP_COOKIE'});
	foreach $pair(@pairs){
		local($name,$value) = split(/=/,$pair);
		$name =~ s/\s//g;
		$DUMMY{$name} = $value;
	}

	@pairs = split(/\,/,$DUMMY{'EZBBS'});
	foreach $pair(@pairs){
		local($name,$value) = split(/\:/,$pair);
		$COOKIE{$name} = $value;
	}

	$c_name = $COOKIE{'name'};
	$c_email = $COOKIE{'email'};
	$c_url = $COOKIE{'url'};
	$c_fntclr = $COOKIE{'fntclr'};
	$c_pwd = $COOKIE{'pwd'};

	if($FORM{'name'}){$c_name = $FORM{'name'};}
	if($FORM{'email'}){$c_email = $FORM{'email'};}
	if($FORM{'url'}){$c_url = $FORM{'url'};}
	if($FORM{'fntclr'}){$c_fntclr =$FORM{'fntclr'};}
	if($FORM{'pwd'}){$c_pwd = $FORM{'pwd'};}
}

# ----- パスワード設定 -----
sub make_pwd{
	local($form_pw) = @_;
	$times = time;
	$salt = substr($times,-2,2);
	return crypt($form_pw,$salt);
}

# ----- パスワード照合 -----
sub match_pwd{
	local($form_pw,$log_pw) = @_;
	if($log_pw =~ /^\$1\$/){$key = 3;}
	else {$key = 0;}

	if(crypt($form_pw,substr($log_pw,$key,2)) eq "$log_pw"){
		return 'OK';
	} else {
		return 'NG';
	}
}

# ----- アクセス拒否 -----
sub deny_host{
	$host = $ENV{'REMOTE_HOST'};
	if ($host eq ''){$host = $ENV{'REMOTE_ADDR'};}

	local($match) = 0;
	foreach (@DENY){
		$_ =~ s/\*/\.\*/g;
		if ($host =~ /$_/){$match = 1; last;}
	}
	if($match){&error("あなたのホストはアクセスできません");}
}

# ----- 現在日時 -----
sub get_time{
	$ENV {'TZ'} = "JST-9";
	local (@week) = ("Sun","Mon","Tue","Wed","Thu","Fri","Sat");
	local ($sec,$min,$hour,$day,$mon,$year,$weekday) = localtime(time);
	$year += 1900;
	$mon++;
	if ($mon < 10) {$mon = "0$mon";}
	if ($day <10) {$day = "0$day";}
	if ($hour <10) {$hour = "0$hour";}
	if($min <10) {$min = "0$min";}
	$weekstr = $week [$weekday];
	$date = "$year/$mon/$day($weekstr) $hour:$min";
}

# ----- ブラウザ情報の取得 -----
sub get_agent{
	$agent = $ENV{'HTTP_USER_AGENT'};

	if ($agent =~ /MSIE 3/i){
		$frm_wid = 500;
		$nam_wid = 35;
		$sub_wid = 50;
		$com_wid = 65;
		$url_wid = 65;
		$res_wid = 55;
	} elsif ($agent =~ /MSIE 4/i || /MSIE 5/i){
		$frm_wid = 500;
		$nam_wid = 40;
		$sub_wid = 50;
		$com_wid = 60;
		$url_wid = 60;
		$res_wid = 50;
	} else {
		$frm_wid = 420;
		$nam_wid = 20;
		$sub_wid = 30;
		$com_wid = 55;
		$url_wid = 50;
		$res_wid = 46;
	}
}
