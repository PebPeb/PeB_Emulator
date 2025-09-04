import inkex

class AddBoundingBoxInfo(inkex.EffectExtension):
    def effect(self):
        for elem in self.svg.selection:
            bbox = elem.bounding_box(transform=True)
            
            elem.set('PeB_x', bbox.left)
            elem.set('PeB_y', bbox.top)
            elem.set('PeB_enable', 1)

if __name__ == '__main__':
    AddBoundingBoxInfo().run()
