
Namespace ne2002
    Public Class dmp_backcaller
        Public Sub New(ByVal oDMPDocument As Object)
            m_oDMPDocument = oDMPDocument
        End Sub
        Public Sub on_page_header()
            m_oDMPDocument.on_page_header()
        End Sub
        Public Sub on_page_footer()
            m_oDMPDocument.on_page_footer()
        End Sub
        Private m_oDMPDocument As Object
    End Class
End Namespace
