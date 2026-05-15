Public Class table_builder
    Public Sub New(oPage As nepage_)

    End Sub
    Public Function attach(oCtrl As Object) As table_builder

        '_current_table = New neuic_table(oCtrl)

        Return Me
    End Function
    Public Function addctrl(iType As Int32, iElementID As Int32) As table_builder
        '_current_element
        Return Me
    End Function
    Public ReadOnly Property newrow As table_builder
        Get
            '_current_row = _current_table.addrow()
            Return Me
        End Get
    End Property
    Public ReadOnly Property newcell As table_builder
        Get
            '_current_cell = _current_row.addcell()

            ' Unmerged change from project 'navo.cocoon.ebwrap (net8.0-windows)' 
            ' Before:
            '             Return _current_cell
            ' After:
            '             Return Current_cell
            Return Me
        End Get
    End Property

    Public Property element As neuic_
        Get
            Return _element
        End Get
        Set(value As neuic_)
            _element = value
        End Set
    End Property

    Public Property cell As neuic_table_cell
        Get
            Return _current_cell
        End Get
        Set(value As neuic_table_cell)
            _current_cell = value
        End Set
    End Property

    Public Property row As neuic_table_row
        Get
            Return _current_row
        End Get
        Set(value As neuic_table_row)
            _current_row = value
        End Set
    End Property

    Private _current_table As neuic_table
    Private _current_row As neuic_table_row
    Private _current_cell As neuic_table_cell
    Private _element As neuic_
End Class
