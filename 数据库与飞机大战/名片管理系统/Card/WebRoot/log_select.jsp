<%@ page language="java" import="java.util.*" pageEncoding="utf-8" errorPage="/error.jsp"%>
<%@ page
	import="com.manager.entity.*,com.manager.dao.*,com.manager.dao.impl.*,com.user.dao.*,com.user.dao.impl.*"%>
<%
	String path = request.getContextPath();
	String basePath = request.getScheme() + "://"
			+ request.getServerName() + ":" + request.getServerPort()
			+ path + "/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<base href="<%=basePath%>">

		<title>日志管理界面</title>

		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
		<meta http-equiv="description" content="This is my page">
		<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
		<link href="css/main.css" rel="stylesheet" type="text/css" />
		<script type="text/javascript" language="javascript"
			src="js/log.js" charset="gbk"></script>
		<script language="javascript" src="datepicker/WdatePicker.js"></script>
		<style type="text/css">
<!--
.STYLE1 {
	font-size: 12px
}

.STYLE2 {
	width: 130px;
	height: 26px;
	margin-left: 10px;
	margin-right: 10px;
}

.STYLE3 {
	color: #707070;
	font-size: 12px;
}
.STYLE4 {
	width: 130px;
	height: 26px;
	margin-left: 10px;
	margin-right: 10px;
}
.STYLE5 {
	color: #0a6e0c;
	font-size: 12px;
}

body {
	margin-top: 0px;
	margin-bottom: 0px;
}

.STYLE7 {
	font-size: 12
}
-->
</style>

	</head>

	<body>
		<div id="right_font">
			<img src="images/main_14.gif" />
			您现在所在的位置：首页   → 日志管理   →
			<strong>日志信息查询</strong>
		</div>
		<form action="LogServlet.action?all=0" method="post">
			<table width="50%" height="10" border="0" cellspacing="10" cellpadding="0" align="center" >
							<tr>
								<td width="27%" height="3" bgcolor="#FFFFFF" margin-top="50px">
									<br></br>按操作者查询
							  </td>
								<td width="73%" height="3" bgcolor="#FFFFFF" margin-top="50px">
									<input type="text" name="user" id="user" class="STYLE2" />
							  </td>
						    </tr>
						    <tr>
								<td width="27%" height="3" bgcolor="#FFFFFF" margin-top="50px">
									按操作时间查询
							  </td>
								<td width="73%" height="3" bgcolor="#FFFFFF" margin-top="50px">
									从&nbsp;<input type="text" name="date1" onFocus="WdatePicker()" />&nbsp;&nbsp;到&nbsp;<input type="text" name="date2" onFocus="WdatePicker()" />
							  </td>
						    </tr>
						    <tr>
								<td colspan="2" align="center" height="4" bgcolor="#FFFFFF" margin-top="50px">
									<input type="submit" name="select" value=""
												style="width: 43px; height: 22px; border: 0; margin-left: -10px; background: url(images/select.gif)">
								</td>
							</tr>
						</table>
		</form>
		<form action="" method="post"
			name="formlog">
			<%
				List<Log> list = (List<Log>) session.getAttribute("log");
				int size;
				if (list == null) {
					size = 0;
					return;
				} else {
					size = list.size();
				}
			%>
			<table width="100%" border="0" cellspacing="0" cellpadding="0" <%=size > 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
			<tr>
				<td height="30">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td>
								&nbsp;
							</td>
							<td style="padding-right: 10px;">
								<div align="right">
									<table border="0" align="right" cellpadding="0" cellspacing="0">
										<tr>
											<td width="60">
												<table width="87%" border="0" cellpadding="0"
													cellspacing="0">
													<tr>
														<td class="STYLE1">
															<div align="center">
																<input type="checkbox" name="all" id="all"
																	value="checkbox" onClick="select_all()"/>
															</div>
														</td>
														<td class="STYLE1">
															<div align="center">
																全选
															</div>
														</td>
													</tr>
												</table>
											</td>
										</tr>
									</table>
								</div>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td>
					<table width="100%" border="0" cellpadding="0" cellspacing="1"
						bgcolor="#c9c9c9">
						<tr>
							<td width="20%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">操作用户</span>
									</strong>
								</div>
							</td>
							<td width="20%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">操作时间</span>
									</strong>
								</div>
							</td>
							<td width="40%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">具体操作</span>
									</strong>
								</div>
							</td>
							<td width="20%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">操作</span>
									</strong>
								</div>
							</td>
						</tr>
						<% 
						for(int i=0;i<list.size();i++)
						{ 
							Log l = list.get(i);
						%>
						<tr>
							<td width="20%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><%=l.getUsersName() %></span>
								</div>
							</td>
							<td width="20%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><%=l.getDate().toLocaleString().split(" ")[0] %></span>
								</div>
							</td>
							<td width="40%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3">
									<% if(l.getAction().equals("新建")){ 
										if(l.getCardName()!=null){
									%>        新建<%=l.getCardName() %>名片
									    <%} 
									      else if(l.getGroupName()!=null){
									    %>    新建<%=l.getGroupName() %>组
									    <%} 
									    } else if(l.getAction().equals("查询")){
									    	if(l.getCardName()!=null){
									    %>    查询<%=l.getCardName() %>名片
									    <%} 
									      else if(l.getGroupName()!=null){
									    %>    查询<%=l.getGroupName() %>组
									    <%}
									    } else if(l.getAction().equals("修改")){
									    	if(l.getCardName()!=null){
									    %>    修改<%=l.getCardName() %>名片
									    <%} 
									      else if(l.getGroupName()!=null){
									    %>    修改<%=l.getGroupName()%>组
									    <%}
									    } else if(l.getAction().equals("删除")){ 
									    	if(l.getCardName()!=null){
									    %>    删除<%=l.getCardName() %>名片
									    <%} 
									      else if(l.getGroupName()!=null){
									    %>    删除<%=l.getGroupName() %>组
									    <%}
									    } else if(l.getAction().equals("向组中添加名片")){
									    	if(l.getCardName()!=null&&l.getGroupName()!=null){
									    %>    将<%=l.getCardName() %>名片添加到<%=l.getGroupName() %>组
									    <%}
									    } else if(l.getAction().equals("查询组中名片")){
									    	if(l.getCardName()!=null&&l.getGroupName()!=null){
									    %>    查询<%=l.getCardName() %>组中<%=l.getGroupName()%>名片
									    <%}
									    } else if(l.getAction().equals("删除组中名片")){
									    	if(l.getCardName()!=null&&l.getGroupName()!=null){
									    %>    将<%=l.getCardName() %>名片从<%=l.getGroupName() %>组中删除
									    <%} 
									    }else if(l.getAction().equals("收藏")){
									    	if(l.getCardName()!=null){
									    %>    收藏<%=l.getCardName() %>名片
									    <%} 
									    } else if(l.getAction().equals("取消收藏")){
									    	if(l.getCardName()!=null){
									    %>    取消对<%=l.getCardName() %>名片的收藏
									    <%}}%>
									</span>
								</div>
							</td>
							<td width="20%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<input type="checkbox" name="delete" 
										value="<%=l.getLogId() %>" />
								</div>
							</td>
						</tr>
						<%} %>
					</table>
				</td>
			</tr>
			<tr>
				<td height="35">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td width="25%" height="29" nowrap="nowrap">
								<table width="342" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td width="44%" class="STYLE1">
											当前页：<%=session.getAttribute("pageNow") %>/<%=session.getAttribute("pageCount") %>页
											每页
											<input name="pageSize" id="pageSize" type="text"
												class="STYLE1" style="height: 20px; width: 25px;" size="5" value="10"/>
										</td>
										<td width="14%" class="STYLE1">
											<img src="images/sz.gif" width="43" height="20"
												onClick="SetNum1()" />
										</td>
										<td width="42%" class="STYLE1">
											<span class="STYLE7">数据总量<%=session.getAttribute("number") %>
											</span>
										</td>
									</tr>
								</table>
							</td>
							<td width="75%" valign="top" class="STYLE1">
								<div align="right">
									<table width="352" height="20" border="0" cellpadding="0"
										cellspacing="0">
										<tr>
											<td width="62" height="22" valign="middle">
												<div align="right">
													<a href="LogServlet.action?all=0&&pageNow=1"><img
															src="images/page_first_1.gif" width="48" height="20" />
													</a>
												</div>
											</td>
											<td width="50" height="22" valign="middle">
												<div align="right">
													<a
														href="LogServlet.action?all=0&&pageNow=<%=(Integer)session.getAttribute("pageNow")-1 %>"><img
															src="images/page_back_1.gif" width="55" height="20" />
													</a>
												</div>
											</td>
											<td width="54" height="22" valign="middle">
												<div align="right">
													<a
														href="LogServlet.action?all=0&&pageNow=<%=(Integer)session.getAttribute("pageNow")+1 %>"><img
															src="images/page_next.gif" width="58" height="20" />
													</a>
												</div>
											</td>
											<td width="49" height="22" valign="middle">
												<div align="right">
													<a
														href="LogServlet.action?all=0&&pageNow=<%=session.getAttribute("number") %>"><img
															src="images/page_last.gif" width="52" height="20" />
													</a>
												</div>
											</td>
											<td width="59" height="22" valign="middle" class="STYLE1">
												<div align="right">
													转到第
												</div>
											</td>
											<td width="25" height="22" valign="middle">
												<span class="STYLE7"> <input name="jump" id="jump"
														type="text" class="STYLE1"
														style="height: 20px; width: 25px;" size="5" /> </span>
											</td>
											<td width="23" height="22" valign="middle" class="STYLE1">
												页
											</td>
											<td width="30" height="22" valign="middle">
												<img src="images/go.gif" width="26" height="20"
													onClick="Jump1()" />
											</td>
										</tr>
									</table>
								</div>
							</td>
			</tr>
		</table>
		<%session.removeAttribute("log");
session.removeAttribute("pageNow");
session.removeAttribute("pageCount");
session.removeAttribute("number"); %>
<table align="center" border="0px" id="result"
				<%=size == 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
				<tr>
					<td align="center" textcolor="red">
						没有日志！！！
					</td>
				</tr>
			</table>
	</body>
</html>
