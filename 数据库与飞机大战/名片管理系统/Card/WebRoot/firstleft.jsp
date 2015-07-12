<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ page
	import="com.manager.entity.*,com.manager.dao.*,com.manager.dao.impl.*"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<link rel="stylesheet" href="resources/css/reset.css" type="text/css" media="screen" />
	  
		<!-- Main Stylesheet -->
		<link rel="stylesheet" href="resources/css/style.css" type="text/css" media="screen" />
		
		<!-- Invalid Stylesheet. This makes stuff look pretty. Remove it if you want the CSS completely valid -->
		<link rel="stylesheet" href="resources/css/invalid.css" type="text/css" media="screen" />	
		
		<!-- Colour Schemes
	  
		Default colour scheme is green. Uncomment prefered stylesheet to use it.
		
		<link rel="stylesheet" href="resources/css/blue.css" type="text/css" media="screen" />
		
		<link rel="stylesheet" href="resources/css/red.css" type="text/css" media="screen" />  
	 
		-->
		
		<!-- Internet Explorer Fixes Stylesheet -->
		
		<!--[if lte IE 7]>
			<link rel="stylesheet" href="resources/css/ie.css" type="text/css" media="screen" />
		<![endif]-->
		
		<!--                       Javascripts                       -->
  
		<!-- jQuery -->
		<script type="text/javascript" src="resources/scripts/jquery-1.3.2.min.js"></script>
		
		<!-- jQuery Configuration -->
		<script type="text/javascript" src="resources/scripts/simpla.jquery.configuration.js"></script>
		
		<!-- Facebox jQuery Plugin -->
		<script type="text/javascript" src="resources/scripts/facebox.js"></script>
		
		<!-- jQuery WYSIWYG Plugin -->
		<script type="text/javascript" src="resources/scripts/jquery.wysiwyg.js"></script>
		
		<!-- jQuery Datepicker Plugin -->
		<script type="text/javascript" src="resources/scripts/jquery.datePicker.js"></script>
		<script type="text/javascript" src="resources/scripts/jquery.date.js"></script>
		<!--[if IE]><script type="text/javascript" src="resources/scripts/jquery.bgiframe.js"></script><![endif]-->

		
		<!-- Internet Explorer .png-fix -->
		
		<!--[if IE 6]>
			<script type="text/javascript" src="resources/scripts/DD_belatedPNG_0.0.7a.js"></script>
			<script type="text/javascript">
				DD_belatedPNG.fix('.png_bg, img, li');
			</script>
		<![endif]-->
  </head>
  
  <body>
  <%
    Users u = (Users)session.getAttribute("users");
    UsersDao dao = new UsersDaoImpl();
    Users_PositionDao updao = new Users_PositionDaoImpl();
    List<Users> list = dao.find("select * from Users where usersId="+u.getUsersId());
    List<Users_Position> list1 = updao.find("select * from Users_Position where usersId="+u.getUsersId());
    Users user = list.get(0);
    Users_Position up = list1.get(0);
%>
    <div id="sidebar"><div id="sidebar-wrapper"> <!-- Sidebar with logo and menu -->
			<!-- Logo (221px wide) -->
			<a href="#"></a>
		  
			<!-- Sidebar Profile links -->
			<ul id="main-nav">  <!-- Accordion Menu -->
				
				<li></li>
				
			    <li><a href="#" class="nav-top-item">用户管理</a>
			      <ul>
			        <li><a href="usermanager/userselect.jsp" target="mainFrame">个人信息查看</a></li>
			        <li><a href="usermanager/passwordalter.jsp" target="mainFrame">密码修改</a></li>
					<li><a href="usermanager/useralter.jsp" target="mainFrame">个人信息修改</a></li>
		          </ul>
		      </li>
		      <li>
				  <a href="#" class="nav-top-item">
					  名片管理				</a>
				  <ul>
					  <li><a href="cardmanage/cardscan.jsp" target="mainFrame">名片一览</a></li>
						<li><a href="cardmanage/addcard.jsp" target="mainFrame">名片生成</a></li>
						<li><a href="CardSelfServlet.action" target="mainFrame">个人名片</a></li>
						<li><a href="CollectionSelectServlet.action" target="mainFrame">名片收藏</a></li>
				  </ul>
			  </li>
				
				<li>
					<a href="#" class="nav-top-item">
						组管理
					</a>
					<ul>
					    <%if(up.getPowerId()==2){ %>
						<li><a href="groupmanage/addgroup.jsp" target="mainFrame">新建组</a></li>
						<%} %>
						<li><a href="groupmanage/groupscan.jsp" target="mainFrame">组一览</a></li>
						 <%if(up.getPowerId()==2){ %>
						<li><a href="GroupSelfServlet.action" target="mainFrame">个人组</a></li>
						<%} %>
					</ul>
				</li> 
				 <li>
				  <a href="#" class="nav-top-item">
					  公司部门管理				</a>
				  <ul>
					  <li><a href="BranchServlet" target="mainFrame">查看公司部门视图</a></li>
				  </ul>
			  </li> 
			      
	</ul> 
			<!-- End #main-nav -->		
		</div></div> <!-- End #sidebar -->
  </body>
</html>
