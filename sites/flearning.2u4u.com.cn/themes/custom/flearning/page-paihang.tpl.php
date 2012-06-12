
<? 
global $user;
if($user->uid>0)//验证用户访问的内容
	print views_embed_view('paihangbang', $display_id = 'paihang_yanzheng');
else//未验证用户访问的内容
	print views_embed_view('paihangbang', $display_id = 'paihang_page');


?>