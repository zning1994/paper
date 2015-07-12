<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@page import="java.net.URLDecoder"%>
<%@ page
	import="java.sql.*,com.manager.dao.*,com.manager.dao.impl.*,com.manager.entity.*,com.manager.util.*"%>
<%@ page import="java.text.SimpleDateFormat,java.util.Date,java.text.ParseException" %>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>
<%
String usersname = "";
String password = "";
try {
	Cookie[] cookies = request.getCookies();
	if (cookies != null) {
		for(Cookie c : request.getCookies()){
			if(c.getName().equals("userkeeping")){
				String value = URLDecoder.decode(c.getValue(), "utf-8");
				usersname = value.split("-")[0];
				password = value.split("-")[1];
				Connection conn = DBConnection.getConnection();
				Statement stmt = conn.createStatement();
				ResultSet rs = stmt.executeQuery("select * from users");
				while (rs.next()) {
					if(rs.getString("usersname").equals(usersname)&&rs.getString("password").equals(password))
					{
						UsersDao dao = new UsersDaoImpl();
						Users user = dao.findByName(usersname);
						Date d = null;
						SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
						try {
							d = sdf.parse(sdf.format(new Date()));
						} catch (ParseException e) {
							e.printStackTrace();
						}
						user.setLastLogin(d);
						dao.update(user);
						session.setAttribute("users",user);
						Users_PositionDao updao = new Users_PositionDaoImpl();
						List<Users_Position> ll = updao.find("select * from users_Position where usersId="+user.getUsersId());
						Users_Position up = ll.get(0);
						if(up.getPowerId()==1)
							response.sendRedirect("main.html");
						else
							response.sendRedirect("index.jsp");
					}
				}
			}
		}
	}
} catch (Exception e) {
	e.printStackTrace();
}
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<!--[if lt IE 7 ]> <html lang="en" class="no-js ie6 lt8"> <![endif]-->
	<!--[if IE 7 ]>    <html lang="en" class="no-js ie7 lt8"> <![endif]-->
	<!--[if IE 8 ]>    <html lang="en" class="no-js ie8 lt8"> <![endif]-->
	<!--[if IE 9 ]>    <html lang="en" class="no-js ie9"> <![endif]-->
	<!--[if (gt IE 9)|!(IE)]><!-->
	<html lang="en" class="no-js">
		<!--<![endif]-->
		<head>
			<base href="<%=basePath%>">
			<title>登录页面</title>
			<meta charset="UTF-8" />
			<!-- <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">  -->
			<title>Login and Registration Form with HTML5 and CSS3</title>
			<meta name="viewport" content="width=device-width, initial-scale=1.0">
			<meta name="description"
				content="Login and Registration Form with HTML5 and CSS3" />
			<meta name="keywords"
				content="html5, css3, form, switch, animation, :target, pseudo-class" />
			<meta name="author" content="Codrops" />
			<link rel="shortcut icon" href="../favicon.ico">
			<link rel="stylesheet" type="text/css" href="css/demo.css" />
			<link rel="stylesheet" type="text/css" href="css/style3.css" />
			<link rel="stylesheet" type="text/css" href="css/animate-custom.css" />
			<script type="text/javascript" language="javascript" src="js/zhuce.js" charset="gbk"></script>
			<script type="text/javascript" src="js/jquery.js"></script>
			<style type="text/css">
.code {
	background: lightblue;
	font-family: Arial;
	font-style: italic;
	color: Red;
	border: 0;
	padding: 2px 3px;
	letter-spacing: 3px;
	font-weight: bolder;
}

.unchanged {
	border: 0;
}
</style>
			<script language="javascript" type="text/javascript">
    
     var code ; //在全局 定义验证码
     function createCode()
      { 
        code = "";
       var codeLength = 4;//验证码的长度
       var checkCode = document.getElementById("checkCode");
       var selectChar =new Array(0,1,2,3,4,5,6,7,8,9,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z');
      //所有候选组成验证码的字符，当然也可以用中文的

       for(var i=0;i<codeLength;i++)
       { 
var charIndex = Math.floor(Math.random()*36);
code +=selectChar[charIndex];
}
       if(checkCode)
        {
          checkCode.className="code";
          checkCode.value = code;
        }
      }
      function validate ()
      {
       var inputCode = document.getElementById("input1").value;
       if(inputCode != code )
        {
           document.getElementById("yanzhengError").innerHTML = "<font style='color:red'>×验证码错误！</font>";
           createCode();//刷新验证码
           return false;
        }
       	else
        {
          document.getElementById("yanzhengError").innerHTML = "<font style='color:green'>√</font>";
          return true;
        }
       }
    </script>
		<script type="text/javascript">
    		$(function(){
				$("#company").change(function(){
        			var sup = document.form_register.company.value;
        			$.post("ajaxCompany",{"company":sup},function(response, suatus){
		       			var rs = response.split("-");
		       			var n = document.getElementById("department").length;
		       			document.getElementById("department").length=0;
		       			for(var i=0; i<rs.length; i++){
		       				var op = new Option(rs[i]);
		   					document.getElementById("department").add(op);
		   				}
		       		});
				});
    		});
		</script>
		<script type="text/javascript">
    		$(function(){
				$("#department").change(function(){
        			var sup = document.form_register.company.value;
        			var sup1 = document.form_register.department.value;
        			$.post("ajaxDepartment",{"company":sup,"department":sup1},function(response, suatus){
		       			var rs = response.split("-");
		       			var n = document.getElementById("position").length;
		       			document.getElementById("position").length=0;
		       			for(var i=0; i<rs.length; i++){
		       				var op = new Option(rs[i]);
		   					document.getElementById("position").add(op);
		   				}
		       		});
				});
    		});
		</script>
		</head>
		<body>
		<body onLoad="createCode();">
		<div class="container">
      <!-- Codrops top bar -->
      <div class="codrops-top">
        <div class="clr">山东科技大学版权所有&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;联系我们：skrj11_2@163.com </div>
      </div>
      <!--/ Codrops top bar -->
      <header>
        <h1>欢迎进入名片管理系统<span></span></h1>
      </header>
      <section>
        <div id="container_demo">
          <!-- hidden anchor to stop jump http://www.css3create.com/Astuce-Empecher-le-scroll-avec-l-utilisation-de-target#wrap4  -->
          <a class="hiddenanchor" id="toregister"></a> <a class="hiddenanchor" id="tologin"></a>
          <div id="wrapper">
            <div id="login" class="animate form" style="top: 16px; height: 436px; left: 3px;">
              <form  action="loginServlet.action" autocomplete="on" method="post" onSubmit="return validate ()" name="formlogin">
                <h1>用户登录</h1>
                <p>&nbsp;</p>
                <p>
                  <label for="username" class="uname" data-icon="u" >用户名</label>
                  <input id="usersname" name="usersname" required type="text" placeholder="6~8个字符，不以数字开头">
                </p>
                <p>
                  <label for="password" class="youpasswd" data-icon="p">密码</label>
                  <input id="password" name="password" required type="password" placeholder="6~12个字符，包括字母、数字、下滑线"/>
                </p>
                <p>验证码
                  <label>
                    <input name="yanzheng" type="text"  id="input1" maxlength="4" style="width:80px" required type="text" onBlur="validate ()"/>
                    <input name="text" type="text" class="unchanged"  id="checkCode" style="width: 80px" onClick="createCode()" readonly />
                    <span id="yanzhengError"></span>
                    <br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<a onClick="createCode()">看不清？换一张</a>
                    </label>
                </p>
				<p class="keeplogin">
                  <input type="checkbox" name="loginkeeping" id="loginkeeping" value="loginkeeping" />
                  <label for="loginkeeping">一周内免登录</label>
                </p>
                <p class="login button">
                  <input name="submit" type="submit" value="登录" />
                </p>
                <p class="change_link" style="top: 454px; left: 0px;"><a href="find_password.jsp" text-align="left" margin-right="200px">忘记密码</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;还没有账号？ <a href="#toregister" class="to_register">立即注册</a> </p>
              </form>
            </div>
            <div id="register" class="animate form">
              <form  action="RegisterServlet.action" autocomplete="on" method="post" name="form_register" onSubmit="return Check()">
                <h1> 用户注册 </h1>
                <p>&nbsp;&nbsp;&nbsp;用户名&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                  <input id="usernamesignup" name="usernamesignup" required type="text" placeholder="6~8个字符，不以数字开头" style="width:200px;" onblur="sendRequest()"/>
                  <span id="usernamesignupError"></span>
                </p>
                <p>&nbsp;&nbsp;&nbsp;&nbsp;邮&nbsp;&nbsp;箱&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                  <input id="emailsignup" name="emailsignup" required type="email" placeholder="例：123456789@qq.com" style="width:200px;" onblur="sendRequest1()"/>
                  <span id="emailsignupError"></span>
                </p>
                <p>&nbsp;&nbsp;&nbsp;&nbsp;密&nbsp;&nbsp;码&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                  <input id="passwordsignup" name="passwordsignup" required type="password" placeholder="密码" style="width:200px;" onblur="checkPassword()"/>
                  <span id="passwordsignupError"></span>
                </p>
                <p>确认密码&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                  <input id="passwordsignup_confirm" name="passwordsignup_confirm" required type="password" placeholder="再次输入" style="width:200px;" onblur="CheckPassword_Confirm()"/>
                <span id="passwordsignup_confirmError"></span>
                </p>公司名称&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                  <select size="1" style="width:180px; height:20px;font-size:13px;" name="company" id="company" >
                    <option value="默认" selected >公司名称</option>
                    <%
								Connection conn = DBConnection.getConnection();
								Statement stmt = conn.createStatement();
								ResultSet rs = stmt.executeQuery("select * from Company");
								while (rs.next()) {
							%>
							<option><%=rs.getString(2)%></option>
							<%
								}
							%>
                  </select><br/>部门名称&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                  <select  size="1" style="width:130px;font-size:13px;" name="department" id="department" >
                    <option value="默认" >部门</option>
                  </select><br/>职务名称&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                  <select size="1" style="width:130px;font-size:13px;" name="position" id="position" >
                    <option value="默认">职务</option>
                  </select>
                </p>
                <p class="signin button">
                  <input name="submit" type="submit" value="注册"/>
                </p>
                <p class="change_link"> 已经拥有账号？ <a href="#tologin" class="to_register"> 立即登录 </a> </p>
              </form>
            </div>
          </div>
        </div>
      </section>
    </div>
		</body>
	</html>