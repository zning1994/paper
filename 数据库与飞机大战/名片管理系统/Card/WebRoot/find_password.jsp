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
	   checkCode.value = "";
       var selectChar =new Array(0,1,2,3,4,5,6,7,8,9,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z');
      //所有候选组成验证码的字符，当然也可以用中文的

       for(var i=0;i<codeLength;i++)
       { 
var charIndex = Math.floor(Math.random()*36);
code +=selectChar[charIndex];
}
if(code.length != codeLength){
   createCode();
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

  </head>
  
  <body>
    <body onLoad="createCode();">
		<div class="container">
      <!-- Codrops top bar -->
      <!--/ Codrops top bar -->
      <section>
        <div id="container_demo">
          <!-- hidden anchor to stop jump http://www.css3create.com/Astuce-Empecher-le-scroll-avec-l-utilisation-de-target#wrap4  -->
          <a class="hiddenanchor" id="toregister"></a> <a class="hiddenanchor" id="tologin"></a>
          <div id="wrapper"></br>
            <div id="login" class="animate form" style="top: 48px; height: 342px; left: 3px;">
              <form  action="new_password.jsp" autocomplete="on" method="post" onSubmit="return validate ()" name="formlogin">
                <h1>找回密码</h1>
                <p>&nbsp;</p>
                <p>
                  <label for="username" class="uname" data-icon="u" >注册邮箱</label><br/>
                  <input id="email" name="email" required type="text" placeholder="注册账号时填写的邮箱" style="width:200px;"  onblur="sendRequest()">
                  <span id="emailError"></span>
                </p>
                <p>验证码
                  <label>
                    <input name="yanzheng" type="text"  id="input1" maxlength="4" style="width:80px" required type="text" onBlur="validate ()"/>
                    <input name="text" type="text" class="unchanged"  id="checkCode" style="width: 80px" onClick="createCode()" readonly />
                    <span id="yanzhengError"></span>
                    <br />
                    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<a onClick="createCode()">看不清？换一张</a>                  </label>
                </p>
                <p>&nbsp;</p>
                <p class="login button">
                  <input name="submit" type="submit" value="提交" />
                </p>
              </form>
            </div>
          </div>
        </div>
      </section>
    </div>
  </body>
</html>
