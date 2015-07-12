<%@ page language="java" import="java.util.*" pageEncoding="utf-8" errorPage="/error.jsp"%>
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

		<title>公司查询</title>

		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
		<meta http-equiv="description" content="This is my page">
		<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
		<link href="css/main.css" rel="stylesheet" type="text/css" />
		<script type="text/javascript" language="javascript" src="js/power.js"
			charset="gbk"></script>
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

body {
	margin-top: 0px;
	margin-bottom: 0px;
}

.STYLE7 {
	font-size: 12px
}

.STYLE9 {
	font-size: 16px
}
-->
</style>
	</head>
	<body>
		<div id="right_font">
			<img src="images/main_14.gif" />
			您现在所在的位置：首页 →
			<strong>权限管理</strong>
		</div>
		<%
        List<Powers> list =(List<Powers>) session.getAttribute("power");
        int size;
		  if (list == null) {
			size = 0;
			return;
		  } else{
			size = list.size(); 
		 }%>
		<table width="100%" border="0" cellspacing="0" cellpadding="0" <%=size > 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
			<tr>
				<td>
					<table width="100%" border="0" cellpadding="0" cellspacing="1"
						bgcolor="#c9c9c9">
						<tr>
							<td width="15.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">权限名</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">用户管理</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">名片管理</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">组管理</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">数据导出</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">审核用户注册信息</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">日志管理</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">参数管理</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">查询组</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">增加组</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">删除组</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">修改组</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">向组中添加名片</span>
									</strong>
								</div>
							</td>
							<td width="6.5%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">修改</span>
									</strong>
								</div>
							</td>
						</tr>
						<%
            for(int j=0;j<list.size();j++){
            	Powers u = list.get(j);
       %>
						<tr>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><%=u.getPowerName() %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getUsersManager()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getCardManager()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getGroupManager()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getDataOut()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getCheckUsers()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getLogManager()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getParameterManager()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getSelectGroup()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getAddGroup()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getDeleteGroup()==1){ %>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getAlterGroup()==1){%>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><% if(u.getAddInGroup()==1){%>√<%} %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE1"><a href="UpdatePower.action?powerId=<%=u.getPowerId() %>">修改</a>
									</span>
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
												onClick="SetNum()" />
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
													<a href="PowerSelectServlet.action?pageNow=1"><img
															src="images/page_first_1.gif" width="48" height="20" />
													</a>
												</div>
											</td>
											<td width="50" height="22" valign="middle">
												<div align="right">
													<a
														href="PowerSelectServlet.action?pageNow=<%=(Integer)session.getAttribute("pageNow")-1 %>"><img
															src="images/page_back_1.gif" width="55" height="20" />
													</a>
												</div>
											</td>
											<td width="54" height="22" valign="middle">
												<div align="right">
													<a
														href="PowerSelectServlet.action?pageNow=<%=(Integer)session.getAttribute("pageNow")+1 %>"><img
															src="images/page_next.gif" width="58" height="20" />
													</a>
												</div>
											</td>
											<td width="49" height="22" valign="middle">
												<div align="right">
													<a
														href="PowerSelectServlet.action?pageNow=<%=session.getAttribute("number") %>"><img
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
													onClick="Jump()" />
											</td>
										</tr>
									</table>
								</div>
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
		</form>
		<%session.removeAttribute("power");
session.removeAttribute("pageNow");
session.removeAttribute("pageCount");
session.removeAttribute("number"); %>
<table align="center" border="0px" id="result"
				<%=size == 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
				<tr>
					<td align="center" textcolor="red">
						没有公司信息！！！
					</td>
				</tr>
			</table>
	</body>
</html>
