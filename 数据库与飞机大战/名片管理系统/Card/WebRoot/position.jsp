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

		<title>职务管理</title>

		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
		<meta http-equiv="description" content="This is my page">
		<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
		<link href="css/main.css" rel="stylesheet" type="text/css" />
		<script type="text/javascript" language="javascript" src="js/position.js"
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
			您现在所在的位置：首页  →
			<strong>职务管理</strong>
		</div>
		<%
        List<Position> list =(List<Position>) session.getAttribute("position");
        int size;
		  if (list == null) {
			size = 0;
			return;
		  } else{
			size = list.size(); 
		 }%>
		 <form action="DeletePosition.action" method="post" name="formposition"> 
		<table width="100%" border="0" cellspacing="0" cellpadding="0" <%=size > 0 ? "style='display:table;'"
					: "style='display:none;'"%>>
			<tr>
				<td height="30">
					<table width="100%" border="0" cellspacing="0" cellpadding="0">
						<tr>
							<td>&nbsp;
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
																	value="checkbox" onClick="select_all()" />
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
											<td width="60"><table width="90%" border="0" cellpadding="0" cellspacing="0">
                  <tr>
                    <td class="STYLE1"><div align="center"><img src="images/001.gif" width="14" height="14" onClick="Add()"/></div></td>
                    <td class="STYLE1"><div align="center" onClick="Add()">新增</div></td>
                  </tr>
              </table></td>
              <td width="60"><table width="90%" border="0" cellpadding="0" cellspacing="0">
                  <tr>
                    <td class="STYLE1"><div align="center"><img src="images/select.png" width="14" height="14" onClick="Select()"/></div></td>
                    <td class="STYLE1"><div align="center" onClick="Select()">查询</div></td>
                  </tr>
              </table></td>
											<td width="52">
												<table width="88%" border="0" cellpadding="0"
													cellspacing="0">
													<tr>
														<td class="STYLE1">
															<div align="center">
																<img src="images/083.gif" width="14" height="14"
																	onClick="Delete()" />
															</div>
														</td>
														<td class="STYLE1">
															<div align="center" onClick="Delete()">
																删除
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
									<strong><span class="STYLE1">公司名</span>
									</strong>
								</div>
						  </td>
							<td width="16%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">部门名</span>
									</strong>
								</div>
						  </td>
						  <td width="16%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">职务名</span>
									</strong>
								</div>
						  </td>
						  <td width="16%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">权限</span>
									</strong>
								</div>
						  </td>
							<td width="15%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">修改</span>
									</strong>
								</div>
						  </td>
							<td width="15%" height="22" bgcolor="#FFFFFF">
								<div align="center">
									<strong><span class="STYLE1">删除</span>
									</strong>
								</div>
						  </td>
						</tr>
						<%
							CompanyDao cd = new CompanyDaoImpl();
											DepartmentDao dd = new DepartmentDaoImpl();
											PowersDao pd = new PowersDaoImpl();
										            for(int j=0;j<list.size();j++){
										            	Position u = list.get(j);
										            	String companyName = cd.findById(u.getCompanyId());
										            	String departmentName = dd.findById(u.getDepartmentId());
										            	String power = pd.findById(u.getPowerId());
						%>
						<tr>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><%=companyName %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><%=departmentName %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><%=u.getPositionName() %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE3"><%=power %></span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<span class="STYLE1"><a href="UpdatePosition.action?positionId=<%=u.getPositionId() %>">修改</a>
									<%System.out.println(u.getPositionId()); %>
									</span>
								</div>
							</td>
							<td height="22" bgcolor="#FFFFFF">
								<div align="center">
									<input type="checkbox" name="delete" 
										value="<%=u.getPositionId() %>" />
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
													<a href="PositionSelectServlet.action?all=1&&pageNow=1"><img
															src="images/page_first_1.gif" width="48" height="20" />
													</a>
												</div>
											</td>
											<td width="50" height="22" valign="middle">
												<div align="right">
													<a
														href="PositionSelectServlet.action?all=1&&pageNow=<%=(Integer)session.getAttribute("pageNow")-1 %>"><img
															src="images/page_back_1.gif" width="55" height="20" />
													</a>
												</div>
											</td>
											<td width="54" height="22" valign="middle">
												<div align="right">
													<a
														href="PositionSelectServlet.action?all=1&&pageNow=<%=(Integer)session.getAttribute("pageNow")+1 %>"><img
															src="images/page_next.gif" width="58" height="20" />
													</a>
												</div>
											</td>
											<td width="49" height="22" valign="middle">
												<div align="right">
													<a
														href="PositionSelectServlet.action?all=1&&pageNow=<%=session.getAttribute("number") %>"><img
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
		<%session.removeAttribute("position");
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
