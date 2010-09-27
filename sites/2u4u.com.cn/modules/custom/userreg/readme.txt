其它异构系统注册接口，提供json格式，drupal模块名字userreg。

（1）post过来的路径:userreg，可接受表单提交，以及URL提交
接收的参数:
name :   用户的用户名，昵称
pass :   用户的密码
mail :   用户注册所用的邮件
source : 用户注册来源，数据类型为字符串，比如shouji,kehuduan，也可以是汉字

（2）返回的json数据结构：
status：表示注册状态，布尔值，TRUE/FALSE
errors：错误信息，成功时，返回空字符串；注册失败时，返回包含错误信息的字符串。

成功时：
array(
  'status' => TRUE,
  'errors' => '',
);

失败时：
array(
  'status' => FALSE,
  'errors' => implode("\n", $errors),
);
