Imports System
Imports System.Runtime.InteropServices
Imports System.Runtime.CompilerServices

Namespace ne2002

    Public Class ne2002trans
        Implements IDisposable
        Public Sub New(ByVal oTransaction As Object)
            m_oTransaction = oTransaction
        End Sub
        Public Overloads Sub Dispose() Implements System.IDisposable.Dispose
            Dispose(True)
            GC.SuppressFinalize(Me)
        End Sub
        Private Overloads Sub Dispose(ByVal bDisposing As Boolean)
            If Not m_oTransaction Is Nothing Then
                If bDisposing Then
                    'noop
                End If
                Marshal.ReleaseComObject(m_oTransaction)
            End If
            m_oTransaction = Nothing
        End Sub
        Protected Overrides Sub Finalize()
            Dispose(False)
            MyBase.Finalize()
        End Sub

        '
        Public Function createadors(ByVal strSQLQuery) As ADODB.Recordset
            Return m_oTransaction.createadors(strSQLQuery)
        End Function

        Private m_oTransaction As Object
    End Class
    Public Class ne2002client
        Implements IDisposable

        Public Sub create(ByVal strApplication As String, ByVal strDBServer As String, ByVal strDBName As String, ByVal bSilent As Boolean)
            m_oClient = CreateObject("navo2002.client")
            m_oClientDoc = m_oClient.document

            Dim str As String = "vn1001=1030 vn1011=1 vn1002=72007 vn1016="
            If bSilent Then
                str = (str & "0")
            Else
                str = (str & "1")
            End If
            str = String.Concat(New String() {str, " vs8003='", strApplication, "' vs8008='", strDBName, "' vs1012='", strDBServer, "'"})
            m_oClientDoc.callcommand(str)
            m_oTopPage = m_oClientDoc.gettoppage
        End Sub
        Public Sub Dispose() Implements IDisposable.Dispose
            Me.Dispose(True)
            GC.SuppressFinalize(Me)
        End Sub

        Private Sub Dispose(ByVal bDisposing As Boolean)
            free_com_object(m_oTopPage)
            m_oTopPage = Nothing

            free_com_object(m_oClientDoc)
            m_oClientDoc = Nothing

            free_com_object(m_oClient)
            m_oClient = Nothing
        End Sub

        Protected Overrides Sub Finalize()
            Me.Dispose(False)
            MyBase.Finalize()
        End Sub
        Public Sub free_com_object(ByVal oComObject As Object)
            If (Not oComObject Is Nothing) Then
                Marshal.ReleaseComObject(oComObject)
            End If
        End Sub

        Public Function get_module(ByVal iModule As Integer) As Object
            Return m_oClientDoc.getmodule(iModule)
        End Function

        Private m_oClient As Object
        Private m_oClientDoc As Object
        Private m_oTopPage As Object
    End Class
End Namespace
