Public Class neuic_
    Friend Shared Function _create_wrapper(ByVal oPage As nepage_, ByVal oCtrl As Object) As neuic_
        Select Case oCtrl.type
            Case Else
                Return New neuic_(oCtrl)
        End Select
    End Function

    Public Sub New(ByVal oCtrl As Object)
        m_oCtrl = oCtrl
    End Sub

    Protected ReadOnly m_oPage As nepage_
    Protected m_oCtrl As Object
End Class

Public Class neuic_container_
    Inherits neuic_

    Public Sub New(ByVal oCtrl As Object)
        MyBase.New(oCtrl)
    End Sub
    Public Function addnew(iType As Int32, iElementID As Int32) As neuic_container_
        'todo
        Return Nothing
    End Function
    Public Function element(ByVal iIndex As Integer) As neuic_
        Return m_oPage.ctrl(m_oCtrl.element(iIndex))
    End Function
End Class

Public Class neuic_table_row
    Inherits neuic_container_

    Public Sub New(ByVal oCtrl As Object)
        MyBase.New(oCtrl)
    End Sub
End Class

Public Class neuic_table_cell
    Inherits neuic_container_

    Public Sub New(ByVal oCtrl As Object)
        MyBase.New(oCtrl)
    End Sub
End Class

Public Class neuic_table
    Inherits neuic_container_

    Public Sub New(ByVal oCtrl As Object)
        MyBase.New(oCtrl)
    End Sub
End Class

Public Class nepage_
    Public Sub New(ByVal oPage As Object)
        m_dictWrappers = New Dictionary(Of Integer, neuic_)()
        m_oPage = oPage
    End Sub

    Public Function ctrl(ByVal idElement As Integer) As neuic_
        Dim oWrapper As neuic_ = Nothing

        If Not m_dictWrappers.TryGetValue(idElement, oWrapper) Then
            Dim oCtrl As Object = m_oPage.ctrl(idElement)
            oWrapper = neuic_._create_wrapper(Me, oCtrl)
            m_dictWrappers.Add(idElement, oWrapper)
        End If

        Return oWrapper
    End Function

    Public Function ctrl(ByVal oCtrl As Object) As neuic_
        Dim oWrapper As neuic_ = Nothing

        If oCtrl Is Nothing Then
            Return Nothing
        Else

            If Not m_dictWrappers.TryGetValue(oCtrl.ident, oWrapper) Then
                oWrapper = neuic_._create_wrapper(Me, oCtrl)
                m_dictWrappers.Add(oCtrl.ident, oWrapper)
            End If

            Return oWrapper
        End If
    End Function

    Private m_oPage As Object
    Private m_dictWrappers As Dictionary(Of Integer, neuic_)
End Class
