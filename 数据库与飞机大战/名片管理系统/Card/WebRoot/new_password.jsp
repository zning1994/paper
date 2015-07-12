<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>找回密码</title>
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
			<script type="text/javascript" language="javascript" src="js/find_password.js" charset="gbk"></script>
			<script type="text/javascript" src="js/jquery.js"></script>
			<style type="text/css">
</style>

  </head>
  
  <body>
    <div class="container">
      <!-- Codrops top bar -->
      <!--/ Codrops top bar -->
      <section>
        <div id="container_demo">
          <!-- hidden anchor to stop jump http://www.css3create.com/Astuce-Empecher-le-scroll-avec-l-utilisation-de-target#wrap4  -->
          <a class="hiddenanchor" id="toregister"></a> <a class="hiddenanchor" id="tologin"></a>
          <div id="wrapper"></br>
            <div id="login" class="animate form" style="top: 48px; height: 342px; left: 3px;">
              <form  action="AlterPasswordServlet.action" autocomplete="on" method="post" onSubmit="return validate ()" name="formlogin">
                <h1>设置新密码</h1>
                <p>&nbsp;</p>
                <input type="text" name="email" id="email" style="display:none" value="<%=request.getParameter("email") %>"/>
                <p>
                  <label for="username" class="uname" data-icon="u" >新密码</label><br/>
                  <input id="password" name="password" required type="text" placeholder="" style="width:200px" onblur="CheckPassword()">
                  <span id="passwordError"></span>
                </p>
				<p>
                  <label for="username" class="uname" data-icon="u" >确认新密码</label><br/>
                  <input id="password_confirm" name="password_confirm" required type="text" placeholder="" style="width:200px" onblur="CheckPassword_Confirm()">
                  <span id="password_confirmError"></span>
                </p>
                <p class="login button"></br></br>
                  <input name="submit" type="submit" value="确定" />
                </p>
              </form>
            </div>
          </div>
        </div>
      </section>
    </div>
  </body>
</html>
