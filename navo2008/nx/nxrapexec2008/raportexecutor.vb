Imports ADODB
Imports System.Runtime.InteropServices
Imports System.Diagnostics
Imports nxappcore
Imports nxuibuilder
Imports nxresultbuilder

<ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_raportexecutor)> _
Public Class raportexecutor
    Private m_oRaportObject As Object
    Private m_oStockRaportObject As Object
    Private m_Sections As nxarray
    Private m_oAspator As aspator
    Private m_oOI As output_item_base
    Private m_iRICC As Integer

    Public Sub New(ByVal oRaportObject As Object, ByVal oStockRaportObject As Object, _
        ByVal oAspator As aspator, ByVal iRICC As Integer)
        m_oRaportObject = oRaportObject
        m_oStockRaportObject = oStockRaportObject
        m_oAspator = oAspator
        m_iRICC = iRICC

        m_Sections = New nxarray
    End Sub

    Public Class section
        Protected m_oParent As raportexecutor
        Private m_iSectionNr As Integer
        Private m_collinxWatchDog As Integer

        'efektywne obiekty raportow obslugujace dane metody
        'jesli custom raport nie implementuje danej metody
        'to wtedy m_oRaportFor * jest ustawiany na stock_raport
        Protected m_oRaportForSectionHeader As Object
        Protected m_oRaportForSectionFooter As Object
        Protected m_oRaportForSectionBody As Object

        Public Sub New(ByVal oParent As raportexecutor, ByVal iSectionNr As Integer, _
            ByVal collinxWatchDog As Integer)
            m_oParent = oParent
            m_iSectionNr = iSectionNr
            m_collinxWatchDog = collinxWatchDog

            m_oLastValue = Nothing
            m_oRaportForSectionHeader = Nothing
            m_oRaportForSectionFooter = Nothing
            m_oRaportForSectionBody = Nothing
        End Sub

        Public Overridable Sub end_section()
            If m_oRaportForSectionFooter Is Nothing Then
                Try
                    m_oRaportForSectionFooter = m_oParent.m_oRaportObject
                    m_oRaportForSectionFooter.section_footer(m_iSectionNr, m_oParent.m_oAspator)
                Catch MME As MissingMethodException
                    m_oRaportForSectionFooter = m_oParent.m_oStockRaportObject
                End Try
            End If
            m_oRaportForSectionFooter.section_footer(m_iSectionNr, m_oParent.m_oAspator)
        End Sub
        Public Overridable Sub begin_section()
            If m_oRaportForSectionHeader Is Nothing Then
                Try
                    m_oRaportForSectionHeader = m_oParent.m_oRaportObject
                    m_oRaportForSectionHeader.section_header(m_iSectionNr, m_oParent.m_oAspator, m_oParent.m_oOI)
                    Exit Sub
                Catch MME As MissingMethodException
                    m_oRaportForSectionHeader = m_oParent.m_oStockRaportObject
                End Try
            End If
            m_oRaportForSectionHeader.section_header(m_iSectionNr, m_oParent.m_oAspator, m_oParent.m_oOI)
        End Sub

        Public Overridable Sub process_row()

        End Sub

        Public Function is_watchdog_change() As Boolean
            If m_collinxWatchDog <> -1 Then
                Debug.Assert(m_collinxWatchDog = m_iSectionNr + m_oParent.m_iRICC - 1)
                Return (m_oLastValue <> m_oParent.m_oOI.m_arrWatchDogs(m_iSectionNr - 1))
            Else
                Return False
            End If
        End Function
        Public Sub update_watchdog()
            If m_collinxWatchDog <> -1 Then
                Debug.Assert(m_collinxWatchDog = m_iSectionNr + m_oParent.m_iRICC - 1)
                m_oLastValue = m_oParent.m_oOI.m_arrWatchDogs(m_iSectionNr - 1)
            End If
        End Sub
        Private m_oLastValue As Object
    End Class

    Public Class body_section
        Inherits section
        Public Sub New(ByVal oParent As raportexecutor)
            MyBase.New(oParent, 0, -1)
        End Sub
        Public Overrides Sub begin_section()
            If m_oRaportForSectionHeader Is Nothing Then
                Try
                    m_oRaportForSectionHeader = m_oParent.m_oRaportObject
                    m_oRaportForSectionHeader.body_section_header(m_oParent.m_oAspator)
                    Exit Sub
                Catch MME As MissingMethodException
                    m_oRaportForSectionHeader = m_oParent.m_oStockRaportObject
                End Try
            End If
            m_oRaportForSectionHeader.body_section_header(m_oParent.m_oAspator)
        End Sub
        Public Overrides Sub end_section()
            If m_oRaportForSectionFooter Is Nothing Then
                Try
                    m_oRaportForSectionFooter = m_oParent.m_oRaportObject
                    m_oRaportForSectionFooter.body_section_footer(m_oParent.m_oAspator)
                Catch MME As MissingMethodException
                    m_oRaportForSectionFooter = m_oParent.m_oStockRaportObject
                End Try
            End If
            m_oRaportForSectionFooter.body_section_footer(m_oParent.m_oAspator)
        End Sub
        Public Overrides Sub process_row()
            If m_oRaportForSectionBody Is Nothing Then
                Try
                    m_oRaportForSectionBody = m_oParent.m_oRaportObject
                    m_oRaportForSectionBody.body_section_body(m_oParent.m_oAspator, m_oParent.m_oOI)
                    Exit Sub
                Catch MME As MissingMethodException
                    m_oRaportForSectionBody = m_oParent.m_oStockRaportObject
                End Try
            End If
            m_oRaportForSectionBody.body_section_body(m_oParent.m_oAspator, m_oParent.m_oOI)
        End Sub
    End Class

    Public Sub add_body_section()
        m_Sections.add(New body_section(Me))
    End Sub
    Public Sub add_grouping_section(ByVal collinxWatchDog As Integer)
        m_Sections.add(New section(Me, m_Sections.count, collinxWatchDog))
    End Sub
    Public Sub perform(ByVal oRecordSetObj As Object)
        Dim oRecordSet As Recordset = oRecordSetObj
        If Not oRecordSet.EOF Then
            m_oOI = output_item_base.rs2oi(oRecordSet, m_iRICC)
            begin_raport_data()
            Do While Not oRecordSet.EOF
                m_oOI = output_item_base.rs2oi(oRecordSet, m_iRICC)
                process_row()
                oRecordSet.MoveNext()
            Loop
            finish_raport_data()
        End If
    End Sub

    Private Sub write_row()
        For Each oSection As section In m_Sections
            oSection.process_row()
        Next
    End Sub

    Private Sub begin_raport_data()
        For Each oSection As section In m_Sections
            oSection.update_watchdog()
            oSection.begin_section()
        Next
    End Sub
    Private Sub finish_raport_data()
        Dim iter As Integer
        For iter = m_Sections.count - 1 To 0 Step -1
            m_Sections(iter).end_section()
        Next
    End Sub

    Private Sub process_row()
        Dim iter As Integer
        For iter = 0 To m_Sections.count - 1
            If m_Sections(iter).is_watchdog_change() Then
                'finish all from iter to m_watchdogUB
                Dim iter2 As Integer
                For iter2 = m_Sections.count - 1 To iter Step -1
                    m_Sections(iter2).end_section()
                    m_Sections(iter2).update_watchdog()
                Next
                'begin new sections
                For iter2 = iter To m_Sections.count - 1
                    m_Sections(iter2).begin_section()
                    m_Sections(iter2).update_watchdog()
                Next
            End If
        Next
        write_row()
    End Sub

End Class
