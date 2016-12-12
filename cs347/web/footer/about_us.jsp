<%@page contentType="text/html" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/tutorstyle.css">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <title>Tutors@JMU - About Us</title>
    </head>
    <body>
        <%
            try {
                Boolean isLoggedInNow
                        = ((Boolean) (session.getAttribute("loggedIn")));
                if (!isLoggedInNow.booleanValue() || isLoggedInNow == null) {
        %>    

        <jsp:include page='<%="../header/header.jsp"%>'/>

        <%
        } else {
        %>    
        <jsp:include page='<%="../header/login_header.jsp"%>'/>
        <%
            }
        } catch (NullPointerException e) {
        %>
        <jsp:include page='<%="../header/header.jsp"%>'/>
        <%
            }
        %>
        <div class="container" id="about-container">
            <h1>About Us</h1>
            <p>This website was created by Joseph Davis,
                Jon Fulk, Conner Turnbull, Patrick Winters</p>
            <button type="button" class="btn btn-default" onClick="history.go(-1);
                    return true;">Go Back</button>
        </div>
        <%@include file="../footer/footer.jsp" %> 
    </body>
</html>
